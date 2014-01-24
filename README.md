## Prerequisites ##

* GCC 4.8 or later
* Cairo 2 or later
* Librsvg 2 or later

## TODO ##

* Crashes when the list terminates with a delimiter, not an element
* Cache the rendered surface of a Symbol until the rendering for other scale requested
* General file-missing fallback
    * symbol loading
    * SVG loading
    * script loading
* Introduce an interface to deal the phenomena that have anything sequential
* Possibility to determine which intermediate is better by previous and next mouth shape
* It may seem to be better to say 'render' command rather 'sync'
* Rotations in degree

## Memo ##

```
      IRenderable
          |
  +-------+----------+
  |       |          |
Shape  ImageSVG   ISymbol
                     |
                   Symbol
                     |
       +-------+-----+------+------+-----+
       |       |     |      |      |     |
     Actor   Head   Eye   Mouth   Leg   Arm
```

* Shape is just vague, it should be split into Path, Rectangle, Circle and whatever
* Classes for parts of a body whould be better to operate through its interface like IHead, IEye ans so on
