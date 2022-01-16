

[Multiplier of the periodic orbit](https://en.wikipedia.org/wiki/Periodic_points_of_complex_quadratic_mappings#Stability_of_periodic_points_(orbit)_-_multiplier) for [complex quadratic polynomial fc(z) = z^2+c](https://en.wikipedia.org/wiki/Complex_quadratic_polynomial)

it can be used for : 
* [multiplier map](https://commons.wikimedia.org/wiki/File:Mandelbrot_set_-_multiplier_map.png)
* internal rays
* checking stability of periodic points z


# examples

```bash
gcc m.c -Wall -lm
./a.out
 c = 0.2547631498472130+0.4981666254092280*I 	 it's multiplier = 0.9527732719049150+0.1058597981813492*I 	 internal radius r = 0.9586361168490332 	 internal angle = 0.0176110004269997  period = 4
```

```bash
c = 0.2547631498472130+0.4981666254092280*I 	 m(c) = 0.9527732719049150+0.1058597981813492*I 	 r(m) = 0.9586361168490332 	 t(m) = 0.0176110004269997 	period = 4
 c = 0.2515187555828430+0.4985671735131340*I 	 m(c) = 0.9986203343241699+0.0473040657755354*I 	 r(m) = 0.9997400896055999 	 t(m) = 0.0075334459994411 	period = 4
 c = 0.2544182852603900+0.4974768962355820*I 	 m(c) = 0.9694382939900951+0.1114651614377388*I 	 r(m) = 0.9758253368655516 	 t(m) = 0.0182194879105317 	period = 4
 c = 0.2547631498472130+0.4981666254092280*I 	 m(c) = 0.9527732719049150+0.1058597981813492*I 	 r(m) = 0.9586361168490332 	 t(m) = 0.0176110004269997 	period = 4
 c = 0.2515187555828430+0.4985671735131340*I 	 m(c) = 0.9986203343241699+0.0473040657755354*I 	 r(m) = 0.9997400896055999 	 t(m) = 0.0075334459994411 	period = 4
 c = 0.2505485440476130+0.4994665165913900*I 	 m(c) = 0.9997587038925655+0.0173230328504826*I 	 r(m) = 0.9999087725768193 	 t(m) = 0.0027574357975608 	period = 4
 c = 0.2478165365298109-0.5027951422378466*I 	 m(c) = 0.9902675065680364+0.0794363627215888*I 	 r(m) = 0.9934484738963123 	 t(m) = 0.0127396650751574 	period = 4
```


```bash
gcc c.c -Wall -lm
./a.out
input : 
	 period = 4 center = 0.2822713907669138+0.5300606175785252*I
	 multiplier : internal angle = 0.0176110004269997 	 internal radius = 0.9586361168490332

otput : c = 0.2547631498472130+0.4981666254092280*I
```


```bash
gcc p.c -Wall -lm
./a.out
period ( c = 0.254763+0.498167) = 4 
```




# files

c programs for computing parameter c from it's multiplier. Use the code from [mandelbrot-numerics library](https://code.mathr.co.uk/mandelbrot-numerics) by [Claude Heiland-Allen](https://mathr.co.uk/)
* [c.c](./src/c.c) 
* [m-interior.c](./src/m-interior.c) 

c program for computing multiplier for given parameter c
* [m.c](./src/m.c) 

c program for computing period
* [p.c](./src/p.c)


# See also
* [period of complex quadratic polynomial](https://github.com/adammaj1/period_complex_quadratic_polynomial) 
* [fractalforums: shaping-spirals](https://fractalforums.org/fractal-mathematics-and-new-theories/28/shaping-spirals/4601/new#new)


# License
[GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007](./src/LICENSE.txt)

# git 


```git
git clone git@github.com:adammaj1/multiplier.git
```



```git
git add README.md
git commit -m "first commit"
git branch -M main
git push -u origin main
```




subdirectory

```git
mkdir images
git add *.png
git mv  *.png ./images
git commit -m "move"
git push -u origin main
```


to overwrite

```git
git mv -f 
```

Local repo 
```
/Dokumenty/julia_p4_spiral/c/multiplier/
```


