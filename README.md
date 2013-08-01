RVCG
====
__RVCG__ is an R-package providing methods for manipulations on triangular meshes by using the API of the [VCGLIB]( http://vcg.isti.cnr.it/~cignoni/newvcglib/html/) library.

#### Installation of the R-package "Rvcg": ####
   0. Make sure to work with the latest version of R and install dependencies (type the following commands into your R terminal): 
               
        install.packages("Rcpp")


* Download the version suitable for your OS from [here](https://github.com/zarquon42b/Rvcg/releases/). 
   Either the compiled package (for Windows and OS X) or the source tarball (Linux).

* Installation command from within R: 
   
        install.packages("Path_to_downloaded_package_Rvcg[Version_OS]",repos=NULL)

* check if the package can be loaded:
        
        load package: library(Rvcg)

#### Installation of the-R package "Rvcg" (latest development code) using *devtools*:: ####


1. install *devtools* from within R (Ubuntu/Debian users will have to install *libcurl4-gnutls-dev* beforehand):

        install.packages("devtools")

2. Install build environment
    * **Windows:** Install latest version of *[Rtools](http://cran.r-project.org/bin/windows/Rtools)*
During installation of *Rtools* make sure to install the *toolchain*, and to select *"Edit the system path"* (and confirming the installers suggestions).
    * **OSX:** Install *[XCODE](https://developer.apple.com/xcode/)*

3. In R run the command:
        
        require(devtools)
        install_url("https://github.com/zarquon42b/Rvcg/archive/master.zip")
    