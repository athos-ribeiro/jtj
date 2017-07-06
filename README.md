Jack, The Janitor
=========================

### The Game

Jack, The Janitor is a puzzle game where the player controls Jack, a school's janitor who must organize the school's warehouse. Jack can push boxes to the left or to the right and jump boxes.

When jack fills an entire row with boxes, they disappear from the screen and go to a small window on the right side of he screen called the closet.

The closet shows how jack organized the rows of boxes. When similar boxes are combined in the closet, Jack gets extra points and some power ups (to be implemented).

The game ends if a falling box hits Jack or if the closet gets full.

### Development

At the moment, Jack, The Janitor is under development by the WareHouse team, in Universidade de Brasília, Brazil.

### Hacking

Jack the Janitor is currently being developed on Linux.

In order to compile it, one must have the SDL and SDL_image libraries. Autotools are also required to generate the makefiles.

The following packages are required for compiling Jack the Janitor:

```
SDL_image-devel
SDL-devel
SDL_ttf-devel
```
  

To compile, run:

bootstrap.sh
./configure
make

then run src/jackthejanitor

### License

Jack, The Janitor is distributed under the GNU Public License, read the COPYING file for more information.
