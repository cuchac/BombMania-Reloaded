
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 * (c) Copyright 2002 Damiano Vitulli <info@spacesimulator.net>
 *
 * ALL RIGHTS RESERVED
 *
 *
 * Tutorial 3: 3d engine - Texture mapping with OpenGL!
 *
 * Include File: texture.cpp
 *
 */

/*
Linux port by Panteleakis Ioannis
mail: pioann@csd.auth.gr

just run: make and you are done.
of course you may need to change the makefile
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GL/glut.h"
#include "objectLoader/texture.h"


/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

/*** Counter to keep track of the last loaded texture ***/
//int num_texture=-1;



/**********************************************************
 *
 * FUNCTION LoadBitmap(char *)
 *
 * This function loads a bitmap file and return the OpenGL reference ID to use that texture
 *
 *********************************************************/
int LoadTexture(const char *filename)
{
   GLuint texture[1];
   glGenTextures(1, texture);
   GLuint num_texture = *texture; // The counter of the current texture is increased

   void * data = NULL;
   int height, width;
   bool hasAlpha=false;

   if(LoadPNG(filename, data, width, height, hasAlpha));
   else
   if(LoadBMP(filename, data, width, height));
   
   if(!data)
      return -1;

   glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter

   // The next commands sets the texture parameters
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function

   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // We don't combine the color with the original surface color, use only the texture map.

   // Finally we define the 2d texture
   glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, ((hasAlpha)?GL_RGBA:GL_RGB), GL_UNSIGNED_BYTE, data);

      fprintf(stderr, "Generating mipmaps for %s ", filename);
   // And create 2d mipmaps for the minifying function
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, ((hasAlpha)?GL_RGBA:GL_RGB), GL_UNSIGNED_BYTE, data);
      fprintf(stderr, " ... done\n");

   free(data); // Free the memory we used to load the texture

   return (num_texture); // Returns the current texture OpenGL ID
}


bool LoadBMP(const char * filename, void * &data, int &width, int &height){
  FILE * file;
  char temp;
  long i;

  MYBITMAPINFOHEADER infoheader;

  if( (file = fopen(filename, "rb"))==NULL) return (-1); // Open the file for reading

  fseek(file, 18, SEEK_CUR);  /* start reading width & height */
  fread(&infoheader.biWidth, sizeof(int), 1, file);

  fread(&infoheader.biHeight, sizeof(int), 1, file);

  fread(&infoheader.biPlanes, sizeof(short int), 1, file);
  if (infoheader.biPlanes != 1) {
    printf("Planes from %s is not 1: %u\n", filename, infoheader.biPlanes);
    return 0;
  }

    // read the bpp
  fread(&infoheader.biBitCount, sizeof(unsigned short int), 1, file);
  if (infoheader.biBitCount != 24) {
    printf("Bpp from %s is not 24: %d\n", filename, infoheader.biBitCount);
    return 0;
  }

  fseek(file, 24, SEEK_CUR);

    // read the data.
  infoheader.data = (char *) malloc(infoheader.biWidth * infoheader.biHeight * 3);
  if (infoheader.data == NULL) {
    printf("Error allocating memory for color-corrected image data\n");
    return 0;
  }

  if ((i = fread(infoheader.data, infoheader.biWidth * infoheader.biHeight * 3, 1, file)) != 1) {
    printf("Error reading image data from %s.\n", filename);
    return 0;
  }

  for (i=0; i<(infoheader.biWidth * infoheader.biHeight * 3); i+=3) { // reverse all of the colors. (bgr -> rgb)
    temp = infoheader.data[i];
    infoheader.data[i] = infoheader.data[i+2];
    infoheader.data[i+2] = temp;
  }


  fclose(file); // Closes the file stream
  data = infoheader.data;
  width = infoheader.biWidth;
  height = infoheader.biHeight;

  fprintf(stderr, "BMP file %s loaded!\n", filename);

  return true;
}

#include <png.h>
#define PNG_HEADER_SIZE 8

bool LoadPNG(const char *name, void * &data, int &width, int &height, bool &isAlpha)
{
  isAlpha=false;
  int pixel_size=3;
  FILE *PNG_file = fopen(name, "rb");
  if (PNG_file == NULL)
  {
    fprintf(stderr, "Can't open PNG file %s\n", name);
    return false;
  }
    
  GLubyte PNG_header[PNG_HEADER_SIZE];
    
  fread(PNG_header, 1, PNG_HEADER_SIZE, PNG_file);
  if (png_sig_cmp(PNG_header, 0, PNG_HEADER_SIZE) != 0)
  {
    //fprintf(stderr, "%s is not a PNG file\n", name);
    return false;
  }
    
  png_structp PNG_reader
      = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (PNG_reader == NULL)
  {
    fprintf(stderr, "Can't start reading PNG file %s\n", name);
    fclose(PNG_file);
    return false;
  }

  png_infop PNG_info = png_create_info_struct(PNG_reader);
  if (PNG_info == NULL)
  {
    fprintf(stderr, "Can't get info for PNG file %s\n", name);
    png_destroy_read_struct(&PNG_reader, NULL, NULL);
    fclose(PNG_file);
    return false;
  }

  png_infop PNG_end_info = png_create_info_struct(PNG_reader);
  if (PNG_end_info == NULL)
  {
    fprintf(stderr, "Can't get end info for PNG file %s\n", name);
    png_destroy_read_struct(&PNG_reader, &PNG_info, NULL);
    fclose(PNG_file);
    return false;
  }
    
  if (setjmp(png_jmpbuf(PNG_reader)))
  {
    fprintf(stderr, "Can't load PNG file %s\n", name);
    png_destroy_read_struct(&PNG_reader, &PNG_info, &PNG_end_info);
    fclose(PNG_file);
    return false;
  }
    
  png_init_io(PNG_reader, PNG_file);
  png_set_sig_bytes(PNG_reader, PNG_HEADER_SIZE);
    
  png_read_info(PNG_reader, PNG_info);
    
  width = png_get_image_width(PNG_reader, PNG_info);
  height = png_get_image_height(PNG_reader, PNG_info);
    
  png_uint_32 bit_depth, color_type;
  bit_depth = png_get_bit_depth(PNG_reader, PNG_info);
  color_type = png_get_color_type(PNG_reader, PNG_info);
    
  if (color_type == PNG_COLOR_TYPE_PALETTE)
  {

      png_set_palette_to_rgb(PNG_reader);

  }

    
  /*if (keep_rgb)
  {*/
    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    {
      png_set_gray_to_rgb(PNG_reader);
    }
  /*}
  else
  {
    if (color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_RGB_ALPHA)
    {
      png_set_rgb_to_gray_fixed(PNG_reader, 1, 0, 0);
    }
  }*/

  if (color_type & PNG_COLOR_MASK_ALPHA)
  {
    isAlpha=true;
    pixel_size=4;
    if (png_get_valid(PNG_reader, PNG_info, PNG_INFO_tRNS))
    {
      png_set_tRNS_to_alpha(PNG_reader);
    }
    else
    {
      png_set_filler(PNG_reader, 0xff, PNG_FILLER_AFTER);
    }
  }
  /*else
  {
    if (color_type & PNG_COLOR_MASK_ALPHA)
    {
      png_set_strip_alpha(PNG_reader);
    }
  }*/
    
  if (bit_depth == 16)
  {
    png_set_strip_16(PNG_reader);
  }
  
    
  png_read_update_info(PNG_reader, PNG_info);
    
  png_byte* PNG_image_buffer = (png_byte*)malloc(pixel_size * width * height);
  png_byte** PNG_rows = (png_byte**)malloc(height * sizeof(png_byte*));
    
  int row;
  for (row = 0; row < height; ++row)
  {
    PNG_rows[height - 1 - row] = PNG_image_buffer + (row * pixel_size * width);
  }
    
  png_read_image(PNG_reader, PNG_rows);
    
  free(PNG_rows);
    
  png_destroy_read_struct(&PNG_reader, &PNG_info, &PNG_end_info);
  fclose(PNG_file);

  data = PNG_image_buffer;

  fprintf(stderr, "PNG file %s loaded!\n", name);
    
  return true;
}
