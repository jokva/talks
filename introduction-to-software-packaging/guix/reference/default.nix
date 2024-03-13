{ stdenv,
  lib,
}:

stdenv.mkDerivation {
    name = "hello";
    version = "2.12.1";
    src = builtins.fetchTarball {
        url = "https://ftp.gnu.org/gnu/hello/hello-2.12.1.tar.gz";
        sha256 = "sha256:0xw6cr5jgi1ir13q6apvrivwmmpr5j8vbymp0x6ll0kcv6366hnn";
    };

    synopsis = "";
    description = "";
    meta = with lib; {
        license = licenses.gpl3Plus;
        description = "GNU hello example package";
        longDescription = "GNU hello example package";
        homepage = "gnu.org";
        platforms = platforms.all;
    };
}
