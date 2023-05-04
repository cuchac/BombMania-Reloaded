/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 * Author: Damiano Vitulli <info@spacesimulator.net>
 *
 * ALL RIGHTS RESERVED
 *
 *
 * Tutorial 4: 3d engine - 3ds models loader
 *
 * Include File: 3dsloader.cpp
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
#include <math.h>
#include <sys/stat.h>

#include "GL/glut.h"

#include "objectLoader/object.h"
#include "objectLoader/3dsloader.h"
#include "objectLoader/texture.h"



/**********************************************************
 *
 * FUNCTION Load3DS (obj_type_ptr, char *)
 *
 * This function loads a mesh from a 3ds file.
 * Please note that we are loading only the vertices, polygons and mapping lists.
 * If you need to load meshes with advanced features as for example:
 * multi objects, materials, lights and so on, you must insert other chunk parsers.
 *
 *********************************************************/


long filelength(int f)
{
    struct stat buf;
    fstat(f, &buf);
    return(buf.st_size);
}



char Load3DS (obj_type_ptr p_object, const char* p_filename)
{
	int i; //Index variable

	FILE *l_file; //File pointer

	unsigned short l_chunk_id; //Chunk identifier
	unsigned int l_chunk_lenght; //Chunk lenght

	unsigned char l_char; //Char variable
	unsigned short l_qty; //Number of elements in each chunk

	unsigned short l_face_flags; //Flag that stores some face information

	if ((l_file=fopen (p_filename, "rb"))== NULL) return 0; //Open the file

	while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file
	//while(!EOF)
	{
		//getch(); //Insert this command for debug (to wait for keypress for each chuck reading)

		fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
		//printf("ChunkID: %x\n",l_chunk_id);
		fread (&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
		//printf("ChunkLenght: %x\n",l_chunk_lenght);

		switch (l_chunk_id)
        {
			//----------------- MAIN3DS -----------------
			// Description: Main chunk, contains all the other chunks
			// Chunk ID: 4d4d
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x4d4d:
			break;

			//----------------- EDIT3DS -----------------
			// Description: 3D Editor chunk, objects layout info
			// Chunk ID: 3d3d (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x3d3d:
			break;

			//--------------- EDIT_OBJECT ---------------
			// Description: Object block, info for each object
			// Chunk ID: 4000 (hex)
			// Chunk Lenght: len(object name) + sub chunks
			//-------------------------------------------
			case 0x4000:
				i=0;
				do
				{
					fread (&l_char, 1, 1, l_file);
                    p_object->name[i]=l_char;
					i++;
                }while(l_char != '\0' && i<200);
			break;

			//--------------- OBJ_TRIMESH ---------------
			// Description: Triangular mesh, contains chunks for 3d mesh info
			// Chunk ID: 4100 (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x4100:
			break;

			//--------------- TRI_VERTEXL ---------------
			// Description: Vertices list
			// Chunk ID: 4110 (hex)
			// Chunk Lenght: 1 x unsigned short (number of vertices)
			//             + 3 x float (vertex coordinates) x (number of vertices)
			//             + sub chunks
			//-------------------------------------------
			case 0x4110:
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
                p_object->vertices_qty = l_qty;
                //printf("Number of vertices: %d\n",l_qty);
                for (i=0; i<l_qty; i++)
                {
					fread (&p_object->vertex[i].x, sizeof(float), 1, l_file);
 					//printf("Vertices list x: %f\n",p_object->vertex[i].x);
                    fread (&p_object->vertex[i].y, sizeof(float), 1, l_file);
 					//printf("Vertices list y: %f\n",p_object->vertex[i].y);
					fread (&p_object->vertex[i].z, sizeof(float), 1, l_file);
 					//printf("Vertices list z: %f\n",p_object->vertex[i].z);
				}
				break;

			//--------------- TRI_FACEL1 ----------------
			// Description: Polygons (faces) list
			// Chunk ID: 4120 (hex)
			// Chunk Lenght: 1 x unsigned short (number of polygons)
			//             + 3 x unsigned short (polygon points) x (number of polygons)
			//             + sub chunks
			//-------------------------------------------
			case 0x4120:
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
                p_object->polygons_qty = l_qty;
                //printf("Number of polygons: %d\n",l_qty);
                for (i=0; i<l_qty; i++)
                {
					fread (&p_object->polygon[i].a, sizeof (unsigned short), 1, l_file);
					//printf("Polygon point a: %d\n",p_object->polygon[i].a);
					fread (&p_object->polygon[i].b, sizeof (unsigned short), 1, l_file);
					//printf("Polygon point b: %d\n",p_object->polygon[i].b);
					fread (&p_object->polygon[i].c, sizeof (unsigned short), 1, l_file);
					//printf("Polygon point c: %d\n",p_object->polygon[i].c);
					fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
					//printf("Face flags: %x\n",l_face_flags);
				}
                break;

			//------------- TRI_MAPPINGCOORS ------------
			// Description: Vertices list
			// Chunk ID: 4140 (hex)
			// Chunk Lenght: 1 x unsigned short (number of mapping points)
			//             + 2 x float (mapping coordinates) x (number of mapping points)
			//             + sub chunks
			//-------------------------------------------
			case 0x4140:
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
				for (i=0; i<l_qty; i++)
				{
					fread (&p_object->mapcoord[i].u, sizeof (float), 1, l_file);
					//printf("Mapping list u: %f\n",p_object->mapcoord[i].u);
                    fread (&p_object->mapcoord[i].v, sizeof (float), 1, l_file);
					//printf("Mapping list v: %f\n",p_object->mapcoord[i].v);
				}
                break;

			//----------- Skip unknow chunks ------------
			//We need to skip all the chunks that currently we don't use
			//We use the chunk lenght information to set the file pointer
			//to the same level next chunk
			//-------------------------------------------
			default:
				 fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
        }
	}
	fclose (l_file); // Closes the file stream
	return (1); // Returns ok
}



/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

//obj_type object; //Now the object is generic, the cube has annoyed us a little bit, or not?

obj_type tempObject;

/**********************************************************
 *
 * FUNCTION ObjLoad(char *p_object_name, char *p_texture_name)
 *
 * This function loads an object and set some object's data
 *
 * Parameters: p_object_name = object name
 *             p_texture_name = texture name
 *             p_pos_x = starting position x coordinate
 *             p_pos_y = starting position y coordinate
 *             p_pos_z = starting position z coordinate
 *             p_rot_x = starting orientation x axis
 *             p_rot_y = starting orientation y axis
 *             p_rot_z = starting orientation z axis
 *
 * Return value: (char) 1 if the object was loaded correctly, 0 otherwise
 *
 *********************************************************/

char ObjLoad(int* object, const char* p_object_name, const char* p_texture_name)
{
   tempObject.vertices_qty=0;
   tempObject.polygons_qty=0;
    
   if(Load3DS (&tempObject, p_object_name)==0) //Object loading
      return(0); 
   tempObject.id_texture=LoadTexture(p_texture_name); // The Function LoadBitmap() returns the current texture ID
   ObjCalcNormals(&tempObject); //Once we have all the object data we need to calculate all the normals of the object's vertices
    
   *object = glGenLists(100);
   glNewList(*object,GL_COMPILE);
   drawObjectToList(&tempObject);
   glEndList();
    
    
   return (1); // If all is ok then return 1
}


/**********************************************************
 *
 * SUBROUTINE ObjCalcNormals(obj_type_ptr p_object)
 *
 * This function calculate all the polygons and vertices' normals of the specified object
 *
 * Input parameters: p_object = object
 *
 **********************************************************/

void ObjCalcNormals(obj_type *p_object)
{
   int i;
   p3d_type l_vect1,l_vect2,l_vect3,l_vect_b1,l_vect_b2,l_normal;  //Some local vectors
   int l_connections_qty[MAX_VERTICES]; //Number of poligons around each vertex

	// Resetting vertices' normals...
   for (i=0; i<p_object->vertices_qty; i++)
   {
      p_object->normal[i].x=0.0;
      p_object->normal[i].y=0.0;
      p_object->normal[i].z=0.0;
      l_connections_qty[i]=0;
   }

   for (i=0; i<p_object->polygons_qty; i++)
   {
      l_vect1.x = p_object->vertex[p_object->polygon[i].a].x;
      l_vect1.y = p_object->vertex[p_object->polygon[i].a].y;
      l_vect1.z = p_object->vertex[p_object->polygon[i].a].z;
      l_vect2.x = p_object->vertex[p_object->polygon[i].b].x;
      l_vect2.y = p_object->vertex[p_object->polygon[i].b].y;
      l_vect2.z = p_object->vertex[p_object->polygon[i].b].z;
      l_vect3.x = p_object->vertex[p_object->polygon[i].c].x;
      l_vect3.y = p_object->vertex[p_object->polygon[i].c].y;
      l_vect3.z = p_object->vertex[p_object->polygon[i].c].z;

	// Polygon normal calculation
      VectCreate (&l_vect1, &l_vect2, &l_vect_b1); // Vector from the first vertex to the second one
      VectCreate (&l_vect1, &l_vect3, &l_vect_b2); // Vector from the first vertex to the third one
      VectDotProduct (&l_vect_b1, &l_vect_b2, &l_normal); // Dot product between the two vectors
      VectNormalize (&l_normal); //Normalizing the resultant we obtain the polygon normal

      l_connections_qty[p_object->polygon[i].a]+=1; // For each vertex shared by this polygon we increase the number of connections
      l_connections_qty[p_object->polygon[i].b]+=1;
      l_connections_qty[p_object->polygon[i].c]+=1;

      p_object->normal[p_object->polygon[i].a].x+=l_normal.x; // For each vertex shared by this polygon we add the polygon normal
      p_object->normal[p_object->polygon[i].a].y+=l_normal.y;
      p_object->normal[p_object->polygon[i].a].z+=l_normal.z;
      p_object->normal[p_object->polygon[i].b].x+=l_normal.x;
      p_object->normal[p_object->polygon[i].b].y+=l_normal.y;
      p_object->normal[p_object->polygon[i].b].z+=l_normal.z;
      p_object->normal[p_object->polygon[i].c].x+=l_normal.x;
      p_object->normal[p_object->polygon[i].c].y+=l_normal.y;
      p_object->normal[p_object->polygon[i].c].z+=l_normal.z;	
   }

   for (i=0; i<p_object->vertices_qty; i++)
   {
      if (l_connections_qty[i]>0)
      {
         p_object->normal[i].x /= l_connections_qty[i]; // Let's now average the polygons' normals to obtain the vertex normal!
         p_object->normal[i].y /= l_connections_qty[i];
         p_object->normal[i].z /= l_connections_qty[i];
      }
   }
}

GLfloat _light1_ambient[]= { 0.1f, 0.1f, 0.1f, 0.1f };
GLfloat _light1_diffuse[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat _light1_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat _light1_position[]= { 100.0f, 0.0f, 200.0f, 1.0f };

GLfloat _mat_metal1_ambient[]= { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat _mat_metal1_diffuse[]= { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat _mat_metal1_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat _mat_metal1_shininess[]= { 1.0f };


void drawObjectToList(obj_type *object, float x, float y, float z, float rotx, float roty, float rotz, float scale)
{
   int l_index;
   glMaterialfv (GL_FRONT, GL_AMBIENT, _mat_metal1_ambient);
   glMaterialfv (GL_FRONT, GL_DIFFUSE, _mat_metal1_diffuse);
   glMaterialfv (GL_FRONT, GL_SPECULAR, _mat_metal1_specular);
   glMaterialfv (GL_FRONT, GL_SHININESS, _mat_metal1_shininess);
   glBindTexture(GL_TEXTURE_2D, object->id_texture);

  /*glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glTranslatef(x, y, z);

   glRotatef(rotx, 1.0f, 0.0f, 0.0f);
   glRotatef(rotz, 0.0f, 0.0f, 1.0f);
   glRotatef(roty, 0.0f, 1.0f, 0.0f);

   glScalef(scale,scale,scale);
  */
   glBegin(GL_TRIANGLES);
   for(l_index=0; l_index<object->polygons_qty; l_index++)
   {
      glNormal3f(object->normal[object->polygon[l_index].a].x, object->normal[object->polygon[l_index].a].y, object->normal[object->polygon[l_index].a].z);
      glTexCoord2f(object->mapcoord[object->polygon[l_index].a].u, object->mapcoord[object->polygon[l_index].a].v);
      glVertex3f(object->vertex[object->polygon[l_index].a].x, object->vertex[object->polygon[l_index].a].y, object->vertex[object->polygon[l_index].a].z);
      glNormal3f(object->normal[object->polygon[l_index].b].x, object->normal[object->polygon[l_index].b].y, object->normal[object->polygon[l_index].b].z);
      glTexCoord2f(object->mapcoord[object->polygon[l_index].b].u, object->mapcoord[object->polygon[l_index].b].v);
      glVertex3f(object->vertex[object->polygon[l_index].b].x, object->vertex[object->polygon[l_index].b].y, object->vertex[object->polygon[l_index].b].z);
      glNormal3f(object->normal[object->polygon[l_index].c].x, object->normal[object->polygon[l_index].c].y, object->normal[object->polygon[l_index].c].z);
      glTexCoord2f(object->mapcoord[object->polygon[l_index].c].u, object->mapcoord[object->polygon[l_index].c].v);
      glVertex3f(object->vertex[object->polygon[l_index].c].x, object->vertex[object->polygon[l_index].c].y, object->vertex[object->polygon[l_index].c].z);
   }
   glEnd();
  //glPopMatrix();
  
  
}
