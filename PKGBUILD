# Maintainer:   fft <anonim288@gmail.com>
# Contributor:  Daniele Basso <daniele05 dot bass at gmail dot com>
# Contributor:  Dimitris Kiziridis <ragouel at outlook dot com>

# TODO
# libmysqlclient.so.20 : whether can use mariadb (likely not)?
# libquazip.so.1: likely related to quazip-legacy, but there only 'libquazip5.so.1' present. Wait for updating to current quazip library (.

# fix working 'preview' functionality. Now IDE crashes with 'Failed to parse extension manifest.' message.
# Seems this is related to QtWebEngineProcess, that can't start. Possibly need to do something with '--disable-gpu'.

pkgname=codelobster
pkgver=1.12.0
pkgrel=2
pkgdesc='Free cross-platform IDE for PHP/HTML/CSS/JavaScript development'
arch=('x86_64')
url="https://www.codelobsteride.com"
license=("custom:${pkgname}")
provides=('codelobster-ide')
depends=(
         'curl'
         'icu56'
         'libidn11'
         'libldap24'
         'nettle6'
         'qt5-multimedia'
         'qt5-networkauth'
         'qt5-svg'
         'qt5-webview'
         'qt5-xmlpatterns'
         'rtmpdump'
         'qt5-websockets'
        )
source=(
        "http://codelobsteride.com/download/codelobsteride-${pkgver}_amd64.deb"
        'LICENSE'
        'cpp_compat.cpp'
        'codelobster.sh'
       )
sha256sums=(
            '9768f39a24699736f282c54da74adc0750fc25344dc8c711e76e73d65ee6dcda'
            '70ce1193a0036cff727f29e1c94bd3ddd61599993ba5d130491037b91158a73a'
            '13d7d92e1134412505ba8790fb9677bbc7f01ece60d760315c126c93f17d67c4'
            '5fe6146d7eeb8a740c60009ea36fc21be56fa5de1db1096b1ee897fc3a289be1'
           )

build() {
    # There are some .so symbol versions mismatches between codelobster and archlinux libraries.
    # Get list of undefined symbols:
    # ldd -r ./CodeLobsterIDE | grep -Po 'undefined symbol: \K[^,]*' | sort -u | c++filt
    # make special compatibility library. Will preload it.
    # based mozilla c++compat (https://hg.mozilla.org/mozilla-central/file/tip/build/unix/stdc++compat/stdc++compat.cpp) and https://stackoverflow.com/a/42414852
    g++ -fPIC -shared -o cpp_compat.so cpp_compat.cpp
}

package() {
    tar xf data.tar.xz -C "${pkgdir}"

    cd "${pkgdir}/opt/codelobsteride"
    rm libasn1.so.8 libcrypto.so.1.1 libcurl.so.4 libhogweed.so.4 libicu* libidn.so.11 liblber-2.4.so.2 libldap_r-2.4.so.2 libnettle.so.6 libQt5* librtmp.so.1 libssh.so.4 libssl.so.1.1 libxcb-* xcbglintegrations/libqxcb-xinerama.so.0
    find ./ -name "*.so*" -exec chmod -x {} +
    chmod a+r ./qt.conf
    install -Dm644 "${srcdir}/LICENSE" -t "${pkgdir}/usr/share/licenses/${pkgname}/"
    rm -r "${pkgdir}/usr/bin/codelobster~" "${pkgdir}/usr/share/applications/codelobsteride.desktop~"
    install -Dm644 "${srcdir}/cpp_compat.so" -t ./
    install -Dm755 "${srcdir}/codelobster.sh" "${pkgdir}/usr/bin/codelobster" # override existing file
}
