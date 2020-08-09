#include "project.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
	Figure *fig,*fig1,*fig2,*fig3,*fig4;

	int n=4,selection;
	Color c;
 	c.red=1.0;
 	c.blue=0;
 	c.green=0;
	fig = start_figure(100.0,50.0);
 	set_thickness_resolution(fig,0.2,0.5);
 	set_color(fig,c);
 	fig1 = start_figure(500.0,250.0);
 	set_thickness_resolution(fig1,0.2,0.5);
 	set_color(fig1,c);
 	fig2 = start_figure(500.0,250.0);
 	set_thickness_resolution(fig2,0.2,0.5);
 	set_color(fig2,c);
 	fig3 = start_figure(200.0,100.0);
 	set_thickness_resolution(fig3,0.2,0.8);
 	set_color(fig3,c);
 	fig4 = start_figure(100.0,50.0);
 	set_thickness_resolution(fig4,0.2,0.8);
 	set_color(fig4,c);
 	fig4->point = (Point2D*)malloc(sizeof(Point2D));
 	fig4->point->x = 0.0;
 	fig4->point->y = 0.0;
 	fig4->point->flag = 0;
 	Point2D *polyline,*centre,*centre1,*width_height;
 	centre = (Point2D*)malloc(sizeof(Point2D));
 	centre->x = 0.0,centre->y = 0.0;
 	centre1 = (Point2D*)malloc(sizeof(Point2D));
 	centre1->x = 0.0,centre1->y = 0.0,centre1->flag = 0;
 	width_height = (Point2D*)malloc(sizeof(Point2D));
 	width_height->x = 80.0,width_height -> y = 40.0;
 	polyline = (Point2D*)malloc(15*sizeof(Point2D));
 	polyline[0].x = 8.0;
 	polyline[0].y = 8.0;
 	polyline[1].x = 50.0;
 	polyline[1].y = 25.0; 
 	polyline[2].x = 37.5;
 	polyline[2].y = 37.5;
 	polyline[3].x = 120.0;
 	polyline[3].y = 37.5;
 	polyline[4].x = -9999;

	printf("1.draw_fx\n2.polyline\n3.polygon\n4.draw_ellipse\n5.append_figures\n6.Exit\nPlease select:");
	scanf("%d",&selection);
	switch(selection){
		case 1:
	 		draw_fx(fig,cos,0,100,1000);
	 		export_eps(fig,"graphic.eps");
	 		break;
	 	case 2:
	 		draw_polyline(fig1,polyline,n);
	 		export_eps(fig1,"polyline.eps");
	 		break;
	 	case 3:
	 		draw_polygon(fig2,polyline);
	 		export_eps(fig2,"polygon.eps");
	 		break;
	 	case 4:
	 		draw_ellipse(fig3,centre,width_height);
	 		export_eps(fig3,"eliphs.eps");
	 		break;
	 	case 5:
	 		draw_polygon(fig2,polyline);
	 		draw_ellipse(fig3,centre,width_height);
	 		append_figures(fig2,fig3);
	 		export_eps(fig2,"append_figures.eps");
	 		break;
	 	case 6:
	 		printf("Quitting\n");
	 		break;
	}
	 
 

 
}
