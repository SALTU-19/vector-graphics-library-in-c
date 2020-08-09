#include "project.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>


Figure * start_figure(double width, double height){
	Figure *figure;
	figure = (Figure*)malloc(sizeof(Figure));
	figure->width = width;
	figure->height = height;
	return figure;
}
void set_thickness_resolution(Figure * fig, double thickness, double resolution){
	fig->thickness = thickness;
	fig->resolution = resolution;
}

void set_color(Figure * fig, Color c){
	fig->color.red = c.red;
	fig->color.green = c.green;
	fig->color.blue = c.blue;
}

void add_point(Point2D *point,double x,double y){
	Point2D *iter;
	iter = point;

	while(iter->next!= NULL){
		iter = iter->next;
	}

	iter->next=(Point2D*)malloc(sizeof(Point2D));
	iter->next->x = x;
	iter->next->y = y;
	iter->next->flag = 0;
	iter->next->next = NULL;

	
}
void export_eps(Figure * fig, char * file_name)
{
	Point2D *iter; 
	FILE *fp;
	fp=fopen(file_name,"w"); 
	fclose(fp);
	fp=fopen(file_name,"a"); 
	fprintf(fp,"%%!PS-Adobe-3.0 EPSF-3.0");
	fprintf(fp,"\n%%%%BoundingBox: %d %d %d %d",20*(int)fig->llx,20*(int)fig->llx,20*(int)fig->width,20*(int)fig->height);
	fprintf(fp,"\n%d setlinewidth",(int)fig->thickness);
	fprintf(fp,"\n%.1f %.1f %.1f setrgbcolor",fig->color.red,fig->color.green,fig->color.blue);
	fprintf(fp,"\n%.1f %.1f moveto",20.0*(fig->point->x+fig->width/2.0),20.0*(fig->point->y+fig->height/2.0));
	iter = fig->point->next;
	while(iter!=NULL)
	 {
	 	fprintf(fp,"\n%.1f %.1f ",20.0*(iter->x+fig->width/2.0),20.0*(iter->y+fig->height/2.0));
		if(iter->flag == 1){
			fprintf(fp,"moveto");
		}
		else {
			fprintf(fp,"lineto");
		}

	 iter=iter->next;
	 }

 fprintf(fp,"\nstroke\n");
 fclose(fp);
}

void draw_fx(Figure * fig, double f(double x), double start_x, double end_x,double step_size){
	double i;
	Point2D *point;
	point = (Point2D*)malloc(sizeof(Point2D));
	point->x = start_x;
	point->y = f(start_x);
	point->flag = 0;

	for(i=start_x; i<=end_x; i+=1.0/step_size){
		add_point(point,i,f(i));
	}

	add_point(point,end_x,f(end_x));

	fig->point = point;
}
void draw_polyline(Figure *fig,Point2D * poly_line, int n){
	int i=1;
	Point2D *point,*iter;
	point = (Point2D*)malloc(sizeof(Point2D));
	iter = point;
	iter->x = poly_line[0].x;
	iter->y = poly_line[0].y;
	iter->next = NULL;
	while(i!=n){
		while(iter->next!=NULL){
			iter=iter->next;
		}
		iter->next = (Point2D*)malloc(sizeof(Point2D));
		iter->next->x = poly_line[i].x;
		iter->next->y = poly_line[i].y;
		iter->next->flag = 0;
		iter->next->next = NULL;
		i++;
	}
	iter -> next -> next = NULL;
	
	fig->point = point;

	
}
void draw_polygon(Figure *fig,Point2D * poly_line){
	
	
	int i=1;
	Point2D *point,*iter;
	point = (Point2D*)malloc(sizeof(Point2D));
	iter = point;
	iter->x = poly_line[0].x;
	iter->y = poly_line[0].y;
	iter->flag = 0;
	iter->next = NULL;
	while(poly_line[i].x!= -9999){
		while(iter->next!=NULL){
			iter=iter->next;
		}
		iter->next = (Point2D*)malloc(sizeof(Point2D));
		iter->next->x = poly_line[i].x;
		iter->next->y = poly_line[i].y;
		iter->next->flag = 0;
		iter->next->next = NULL;
		i++;
	}
	iter -> next -> next = (Point2D*)malloc(sizeof(Point2D));
	iter -> next -> next->x = poly_line[0].x;
	iter -> next -> next->y = poly_line[0].y;
	iter -> next -> next-> flag = 0;
	iter -> next -> next->next = NULL;
	fig->point = point;

	

}
void merge(Point2D *p1,Point2D *p2)
{
	Point2D *iter=p1;

	while(iter->next!=NULL){
		iter=iter->next;
	}
	iter->next=p2; 
}
void draw_ellipse(Figure *fig,Point2D * centre, Point2D * width_height){
	Figure *fig2;  
	Color c;
 	c.red=1.0;
 	c.blue=0;
 	c.green=0;

	fig2 = start_figure(200.0,100.0);
 	set_thickness_resolution(fig2,0.2,0.8);
 	set_color(fig2,c);
 	

	double a = width_height->x;
	double b = width_height->y;


	double pos_ellipse_func(double x){
		return   sqrt((1-((x*x)/(a*a)))*(b*b));
	} 
	double neg_ellipse_func(double x){
		return  -sqrt((1-((x*x)/(a*a)))*(b*b));
	}
	draw_fx(fig,pos_ellipse_func,-a,a,100);
	draw_fx(fig2,neg_ellipse_func,-a,a,100);
	fig2->point->flag = 1;
	merge(fig->point,fig2->point);	

}
void append_figures(Figure * fig1, Figure * fig2){
	fig2->point->flag = 1;
	merge(fig1->point,fig2->point);

}


