

[Multiplier of the periodic orbit](https://en.wikipedia.org/wiki/Periodic_points_of_complex_quadratic_mappings#Stability_of_periodic_points_(orbit)_-_multiplier) for [complex quadratic polynomial fc(z) = z^2+c](https://en.wikipedia.org/wiki/Complex_quadratic_polynomial)

it can be used for : 
* [multiplier map](https://commons.wikimedia.org/wiki/File:Mandelbrot_set_-_multiplier_map.png)
* internal rays
* checking stability of periodic points z


# examples

```bash
gcc m.c -Wall -lm
./a.out
 c = 0.2547631498472130+0.4981666254092280*I 	 it's multiplier = 0.9527732719049150+0.1058597981813492*I 	 internal radius r = 0.9586361168490332 	 internal angle = 0.0176110004269997 
```




# files

c programs 
* [c.c](./src/c.c) : compute parameter c from it's multiplier
* [m.c](./src/m.c) : compute multiplier for given parameter c

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


