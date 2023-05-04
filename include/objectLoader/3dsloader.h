/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 *  Author: Damiano Vitulli <info@spacesimulator.net>
 *
 * ALL RIGHTS RESERVED
 *
 *
 * Tutorial 4: 3d engine - 3ds models loader
 * 
 * File header: 3dsloader.h
 *  
 */

/*
Linux port by Panteleakis Ioannis
mail: pioann@csd.auth.gr

just run: make and you are done.
of course you may need to change the makefile
*/
#ifndef _3DSLOADER_H
#define _3DSLOADER_H

#include "mat_vect.h"
#include "GL/glut.h"

#define MAX_VERTICES 40000 // Max number of vertices (for each object)
#define MAX_POLYGONS 40000 // Max number of polygons (for each object)


/**********************************************************
 *
 * TYPES DECLARATION
 *
 *********************************************************/

// Our vertex type
typedef struct{
   float x,y,z;
}vertex_type;

// The polygon (triangle), 3 numbers that aim 3 vertices
typedef struct{
   int a,b,c;
}polygon_type;

// The mapcoord type, 2 texture coordinates for each vertex
typedef struct{
   float u,v;
}mapcoord_type;

// The object type
typedef struct{

   char name[200]; // Name of the object
   int vertices_qty; // Number of vertices
   int polygons_qty; // Number of polygons
   vertex_type vertex[MAX_VERTICES]; // Array of vertices
   vertex_type normal[MAX_VERTICES]; // Array of the vertices' normals
   polygon_type polygon[MAX_POLYGONS]; // Array of polygons (numbers that point to the vertices' list)
   mapcoord_type mapcoord[MAX_VERTICES]; // Array of U,V coordinates for texture mapping

   int id_texture; // Number of the texture

}obj_type, *obj_type_ptr;



/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

//extern obj_type object;



/**********************************************************
 *
 * FUNCTIONS DECLARATION
 *
 *********************************************************/

void drawObjectToList(obj_type *object, float x=0, float y=0, float z=0, float rotx=0, float roty=0, float rotz=0, float scale=1);
extern char ObjLoad(int *object, const char *p_object_name, const char *p_texture_name);
extern void ObjCalcNormals(obj_type *p_object);

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

extern char Load3DS (obj_type_ptr p_object, const char *filename);

extern int LoadBitmap(const char *filename);

extern char ObjLoad(obj_type *p_object, const char *p_object_name, const char *p_texture_name);
extern void ObjCalcNormals(obj_type *p_object);

#endif