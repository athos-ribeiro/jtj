Name:	jackthejanitor
Version:	1.0.1
Release:	1%{?dist}
Summary:	Puzzle game where you have to unstack boxes

License:	GPLv3+
URL:		https://unbgames.lappis.rocks/games/
Source0:	https://github.com/athos-ribeiro/jtj/archive/%{version}/%{name}-%{version}.tar.gz

BuildRequires:	autoconf
BuildRequires:	automake
BuildRequires:	make
BuildRequires:	gcc
BuildRequires: SDL_image-devel
BuildRequires: SDL-devel
BuildRequires: SDL_ttf-devel
Requires:	SDL_image
Requires:	SDL
Requires:	SDL_ttf

%description
Jack, The Janitor is a puzzle game where the player controls Jack, a school's
janitor who must organize the school's warehouse. Jack can push boxes to the
left or to the right and jump boxes.

When jack fills an entire row with boxes, they disappear from the screen and go
to a small window on the right side of he screen called the closet.

The closet shows how jack organized the rows of boxes. When similar boxes are
combined in the closet, Jack gets extra points and some power ups (to be
implemented).

The game ends if a falling box hits Jack or if the closet gets full.

%prep
%autosetup -n jtj-%{version}

# This is needed so jtj can find the game resources. These changes should be
# applied upstream instead. Also, the game resources should be shipped in a
# different package to comply with the Fedora Project packaging guidelines.
sed -i 's|resources|%{_prefix}/games/%{name}/resources|g' src/*.cpp
# /usr/games/jackthejanitor/ = +26 characters.
# 26 + 26 = 52
# Note that those string sizes are wrong and should also be fixed upstream.
sed -i 's/26/52/g' src/*.cpp


%build
autoreconf --install
%configure
make %{?_smp_mflags}


%install
make install DESTDIR=%{buildroot}


%files
%{_bindir}/jackthejanitor
%{_prefix}/games/%{name}
%license COPYING
%doc %{_docdir}/%{name}



%changelog
* Thu Jul 06 2017 Athos Ribeiro <athoscr@fedoraproject.org> - 1.0.1-1
- Initial package
