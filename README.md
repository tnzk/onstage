## Prerequisites ##

* GCC 4.8 or later
* Librsvg 2 or later

## TODO ##

* Crashes when the list terminates with a delimiter, not an element
* Cache the rendered surface of a Symbol until the rendering for other scale requested
* General file-missing fallback
    * symbol loading
    * SVG loading
    * script loading

## Inheritance ##

      IRenderable
          |
  +-------+----------+
  |       |          |
Shape  ImageSVG   ISymbol
                     |
                  Item(*)
                     |
       +-------+-----+------+------+-----+
       |       |     |      |      |     |
     Actor   Head   Eye   Mouth   Leg   Arm

* Item is planned to be renamed as Symbol
* Shape is just vague, it should be split into Path, Rectangle, Circle and whatever
* Classes for parts of a body whould be better to operate through its interface like IHead, IEye ans so on
