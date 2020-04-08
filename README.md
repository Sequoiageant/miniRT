# miniRT
**In Progress...**
*First graphic project in 42 School. Allows you to generate scenes in 3D containing simple objects like spheres, planes, squares, cylinders and triangles.*

## Installation and uses
1. Compile using make

2. Execute the binary made with:
	* firt argument (mandatory): the path to the scene you want to generate
	* second argument (optionnal): "-save" to save the generated image as [.bmp] into bmp_saved/

example.
```sh
$ make
$ ./minirt scenes/scene2.rt
```
or
```sh
$ make
$ ./minirt scenes/147_spheres.rt -save
```
## Configuration file
**The configuration file must respect some rules:**
* The first letter represents the Type of the property
	* **R: Resolution**
	* **A: Ambiant light**
	* **c: Cameras**
	* **l: Spot lights**
	* **sp: Sphere**
	* **pl: Plane**
	* **sq: Square**
	* **cy: Cylinder**
	* **tr: Triangle**
* The **R** is unique and represented by 2 integers > 0.
* The **A** is unique and in the range [0.0; 1.0].
* All **vectors** *(ie. 30.0,-10.0,-50.0)* must contain 3 integers or floats components, separated by a ',', without spaces.
	* In addition **directionals vectors** *(ie. 0.0,1.0,-1.0)* are in range [-1.0; 1.0].
* Cameras are in the range [0; 180] degrees.
* Lights are in the range [0.0; 1.0].
* Unique properties of Objects (**radius** for sp and cy, **height** for sq and cy) must be positive.
* A color *(ie. 246,24,251)* is defined by three ints in range [0; 255].
* A commented line by **"#"** will not been taken into consideration by the program.
* Every other property as those mentioned obove will result in an error.

**Example of configuration file**
>	# Image Resolution (unique)
>	R	850	620
>	
>	# Ambiant light (unique)
>	A	0.7		255,255,255
>	
>	# Cameras (at least one)
>	c	0.0,0.0,0.0		0,0,1	60
>	
>	# Spot lights
>	l	40.0,-10.0,0.0		0.5		255,255,255
>	l	30.0,-10.0,-50.0	0.8		255,255,255
>	
>	# Objects
>	sp	-6.0,3.0,-30.0	10.0  100,56,255
>	sp	0.0,-3.0,-30.0	10.0  255,69,255
>	sp	6.0,3.0,-30.0	10.0  255,69,50
>	sp	5.0,-8.0,-30.0	4.0  255,69,50
>	
>	pl	0.0,15.0,0.0		0.0,-1.0,0.0		255,255,0
>	pl	-8.0,0.0,0.0		1.0,0.0,0.0			50,255,200
>	pl	0.0,0.0,-51.0		0.0,0.0,1.0			150,200,0
>	
>	sq	3.0,-5.0,-20.0		1.0,0.0,0.5		14	255,150,0
>	tr	-4.0,2.0,-10.0		-2.0,10.0,-50.0		-8.0,-10.0,-25.0	150,50,0
>	cy 20.0,6.0,-50   0.0,-1.0,0.0    8.0 15.0	246,24,251
