Jack, The Janitor
=========================

### The Game

Jack, The Janitor is a puzzle game where the player controls Jack, a school's
janitor who must organize the school's warehouse. Jack can push boxes to the
left or to the right and jump boxes.

When jack fills an entire row with boxes, they disappear from the screen and go
to a small window on the right side of he screen called the closet.

The closet shows how jack organized the rows of boxes. When similar boxes are
combined in the closet, Jack gets extra points and some power ups (to be
implemented).

The game ends if a falling box hits Jack or if the closet gets full.

### Development

At the moment, Jack, The Janitor is under development by the WareHouse team, in
Universidade de Brasília, Brazil.

### Installing Jack, The Janitor

For now, we recommend downloading one of our packages from [UnB
Games](https://unbgames.lappis.rocks/games/).  Currently, we only
provide .deb and .rpm packages, which should run in any Debian or
Fedora based GNU/Linux distributions.

If you want to compile the game yourself, check the Hacking section
below. If you still have any doubts on the installation process,
reading the RPM package spec file in jackthejanitor.spec may help.

### Hacking

Jack the Janitor is currently being developed on Linux.

The following packages are required for compiling Jack the Janitor:

```
autoconf
automake
make
gcc
SDL_image-devel
SDL-devel
SDL_ttf-devel
```

To compile, run:

```
bootstrap.sh
./configure
make
```

then run `src/jackthejanitor`

Note that to run jackthejanitor, the following packages must be installed:

```
SDL_image
SDL
SDL_ttf
```

### License

Copyright 2017 WareHouse (See the AUTHORS file) <athoscr@fedoraproject.org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
