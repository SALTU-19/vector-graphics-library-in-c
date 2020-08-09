#ifndef PROJECT
#define PROJECT

typedef struct Point2D{
	double x,y;
	struct Point2D *next;
	int flag;  
}Point2D;

typedef struct color{
	double red,green,blue;
}Color;

typedef struct figure{
	double width, height,resolution,thickness,llx,lly; 
	Color color;
 	Point2D *point;
}Figure;

Figure * start_figure(double width, double height);

void set_thickness_resolution(Figure * fig, double thickness, double resolution);

void set_color(Figure * fig, Color c);

void add_point(Point2D *point,double x,double y);

void export_eps(Figure * fig, char * file_name);

void draw_fx(Figure * fig, double f(double x), double start_x, double end_x,double step_size);

void draw_polyline(Figure *fig,Point2D * poly_line, int n);

void draw_polygon(Figure *fig,Point2D * poly_line);

void merge(Point2D *p1,Point2D *p2);

void draw_ellipse(Figure *fig,Point2D * centre, Point2D * width_height);

void append_figures(Figure * fig1, Figure * fig2);




#endif