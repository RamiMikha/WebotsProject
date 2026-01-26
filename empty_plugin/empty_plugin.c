#include <plugins/physics.h>
#include <stdio.h>

/* This is called when the plugin is loaded */
void webots_physics_init() {
    printf("Empty Webots plugin loaded. \n");
}

/* Special initialization - required by Webots */
/*Webots was giving an error without it*/
void physics_special_init() {
    //can perform any spcial initialization here if needed
    //can be left blank if none are required by our plugin
}

/* This is called every simulation step */
void webots_physics_step() {
    // do nothing
}

/* Called when the plugin is unloaded */
void webots_physics_cleanup() {
    printf("Empty Webots plugin unloaded. \n");
}