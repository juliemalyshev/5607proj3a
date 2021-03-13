
//Set the global scene parameter variables
//TODO: Set the scene parameters based on the values in the scene file

#ifndef PARSE_VEC3_H
#define PARSE_VEC3_H

#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>

//Camera & Scene Parmaters (Global Variables)
//Here we set default values, override them in parseSceneFile()

//Image Parmaters
int img_width = 800, img_height = 600;
std::string imgName = "raytraced.png";

//Camera Parmaters
vec3 eye = vec3(0,0,0);
vec3 forward = vec3(0,0,-1).normalized();
vec3 up = vec3(0,1,0).normalized();
vec3 right = vec3(-1,0,0).normalized();
float halfAngleVFOV = 35;

//Scene (Sphere) Parmaters
vec3 spherePos = vec3(0,0,2);
float sphereRadius = 1;

//Color
float  red,green,blue;

void parseSceneFile(std::string fileName){
  //TODO: Override the default values with new data from the file "fileName"
  FILE *fp;
  long length;
  char line[1024]; //Assumes no line is longer than 1024 characters!

  std::string str = fileName;
  const char *cstr = str.c_str();

  // open the file containing the scene description
  fp = fopen(cstr, "r");

  // check for errors in opening the file
  if (fp == NULL) {
    printf("Can't open file '%s'\n", fileName.c_str());
    return;
  }



  //Loop through reading each line
  while( fgets(line,1024,fp) ) { //Assumes no line is longer than 1024 characters!
    if (line[0] == '#'){
      printf("Skipping comment: %s", line);
      continue;
    }

    char command[100];
    char lineComp[100];
    int fieldsRead = sscanf(line,"%s ",command); //Read first word in the line (i.e., the command type)
    std::string commandStr = command;

    if (fieldsRead < 1){ //No command read
     //Blank line
     continue;
    }

    if (commandStr == "sphere:"){ //If the command is a sphere command
       int x,y,z;
       float r;
       sscanf(line,"sphere: %i %i %i %f", &x, &y, &z, &r);
       //printf(line);
       printf("Sphere as position (%i,%i,%i) with radius %f\n",x,y,z,r);
       sphereRadius = r;
       spherePos = vec3(x,y,z);


    }
    else if (commandStr == "background:"){ //If the command is a background command
       float r,g,b;
       sscanf(line,"background: %f %f %f", &r, &g, &b);
       red = r;
       green = g;
       blue = b;
       printf("Background color of (%f,%f,%f)\n",red,green,blue);
    }
    else if (commandStr == "output_image:"){ //If the command is an output_image command
       char outFile[1024];
       sscanf(line,"output_image: %s", outFile);

       imgName = outFile;
       printf("Render to file named: %s\n", outFile);
    }
    else if (commandStr == "camera_pos:"){ //If the command is an output_image command
       int x,y,z;
       sscanf(line,"camera_pos: %d %d %d", &x, &y, &z);
       vec3 newPos = vec3(x,y,z);

       eye = newPos;
       //printf("Render to file named: %s\n", outFile);
    }
    else if (commandStr == "camera_fwd:"){ //If the command is an output_image command
       float x,y,z;
       sscanf(line,"camera_fwd: %f %f %f", &x, &y, &z);
       printf("camera_fwd: %f %f %f", x, y, z);
       vec3 newFwd = vec3(x,y,z).normalized();
       forward = newFwd;
       //printf("Render to file named: %s\n", outFile);
    }
    else if (commandStr == "camera_up:"){ //If the command is camera_up command
       float x,y,z;
       sscanf(line,"camera_up: %f %f %f", &x, &y, &z);
       printf("camera_up: %f %f %f", x, y, z);
       vec3 newUp = vec3(x,y,z).normalized();
       up = newUp;

       printf("\n");
    }
    else if (commandStr == "camera_fov_ha:"){ //If the command is an output_image command
       float a;
       sscanf(line,"camera_fov_ha: %f", &a);
       halfAngleVFOV = a;
       //printf("Render to file named: %s\n", outFile);
    }
    else if (commandStr == "image_resolution:"){ //If the command is an output_image command
       int x,y;
       sscanf(line,"image_resolution: %d %d", &x, &y);
       img_width = x;
       img_height = y;
       //printf("Render to file named: %s\n", outFile);
    }
    else {
      printf("WARNING. Unknown command: '%s'\n",command);
    }
  }
  //TODO: Create an orthagonal camera basis, based on the provided up and right vectors
  printf("Orthagonal Camera Basis:\n");
  forward = forward.normalized();
  up = up.normalized();
  right = cross(up,forward).normalized();
  up = cross(forward, right).normalized();
  //up = cross(rightward,forward).normalized();


  //forward = cross(up,right).normalized();
  printf("forward: %f,%f,%f\n",forward.x,forward.y,forward.z);
  printf("right: %f,%f,%f\n",right.x,right.y,right.z);
  printf("up: %f,%f,%f\n",up.x,up.y,up.z);
}

#endif
