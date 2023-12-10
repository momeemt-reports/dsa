{ pkgs ? import ./nix/pkgs.nix }:
pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    llvmPackages_16.libcxxClang
    llvmPackages_16.clang-unwrapped
    gnumake
    gnuplot
    cunit
    doxygen
  ];

  shellHook = ''
    export C_INCLUDE_PATH=$(clang -E -x c - -v < /dev/null 2>&1 | sed -n '/#include <...> search starts here:/,/End of search list./p' | grep -vE '#include|End of search list.' | sed 's/ (framework directory)//' | sed 's/^ //' | tr '\n' ':' | sed 's/:$$//')
    export C_INCLUDE_PATH=$C_INCLUDE_PATH$(pwd)"/headers"
    export CUNIT_INCLUDE_DIR="${pkgs.cunit}/include"
  '';
}
