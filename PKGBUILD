# Maintainer: clausmarian

pkgname=hangman
pkgver=1.0
pkgrel=1
pkgdesc="Simple single-player game"
arch=('any')
url="https://github.com/clausmarian/hangman"
license=('MIT')
makedepends=('git')
source=("$pkgname::git://github.com/clausmarian/$pkgname.git")
md5sums=('SKIP')

build() {
	cd "$pkgname/src"
	g++ -std=c++17 $pkgname.cpp -o $pkgname
}

package() {
	cd "$pkgname"
	install -Dm755 ./src/$pkgname "$pkgdir/usr/bin/$pkgname"
	install -Dm644 ./${pkgname}_icon.png "$pkgdir/usr/share/pixmaps/${pkgname}_icon.png"
	install -Dm644 ./$pkgname.desktop "$pkgdir/usr/share/applications/$pkgname.desktop"
	install -Dm644 ./README.md "$pkgdir/usr/share/doc/$pkgname/README.md"
}
