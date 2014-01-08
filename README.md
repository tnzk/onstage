## Prerequisites ##

* GCC 4.8 or later
* Librsvg 2 or later

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

* Item はそのうち Symbol に変更
* Shape は Path, Rectangle とかに分割かなあ
* Head や Eye はインターフェイスにして人間以外も扱えるようにしたいけどまずは放置でいい
