(use-modules (guix)
             (guix packages)
             (guix download)
             (guix build-system gnu)
             (guix licenses))

(define-public hello
  (package
    (name "hello")
    (version "1.12.1")
    (source
      (origin
        (method url-fetch)
        (uri (string-append "https://ftp.gnu.org/gnu/" name "/" name "-" version
                          ".tar.gz"))
        (sha256
            (base32 "086vqwk2wl8zfs47sq2xpjc9k066ilmb8z6dn0q6ymwjzlm196cd"))))
    (build-system gnu-build-system)
    (home-page "gnu.org")
    (synopsis "GNU hello example package")
    (description "GNU hello example package")
    (license gpl3+)))

hello
