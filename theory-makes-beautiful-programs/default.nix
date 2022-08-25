with import <nixpkgs> {};

stdenv.mkDerivation {
  name = "talk-techtown-2022";
  buildInputs = [(texlive.combine {
                    inherit (texlive)
                      scheme-small

                      # Add other LaTeX libraries (packages) here as needed, e.g:
                      # stmaryrd amsmath pgf
                      beamer
                      listings
                      hyperref

                      xcolor

                      # build tools
                      latexmk
                      ;
                  })
                ];
  src = ./.;
  buildPhase = "make";

  meta = with lib; {
    description = "Slides for techtown 2022";
    license = licenses.bsd3;
  };
}
