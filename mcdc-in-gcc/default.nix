with import <nixpkgs> {};

stdenv.mkDerivation {
  name = "talk-techtown-2022";
  buildInputs = [(texlive.combine {
                    inherit (texlive)
                      scheme-small

                      # Add other LaTeX libraries (packages) here as needed, e.g:
                      # stmaryrd amsmath pgf
                      algorithms
                      algorithmicx
                      beamer
                      listings
                      hyperref
                      xcolor
                      braket
                      amsmath
                      pgf # tikz
                      pgfplots

                      # build tools
                      latexmk
                      ;
                  })
                  graphviz
                  dot2tex
                ];
  src = ./.;
  buildPhase = "make";

  meta = with lib; {
    description = "Slides for techtown 2022";
    license = licenses.bsd3;
  };
}
