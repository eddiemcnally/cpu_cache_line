Refer to the wiki for an overview.

To build:
---------
run 'make'

Generated binary is called cache_line_test.


To run:
-------
Change to scripts directory:
	cd ./scripts

Run the tests:
	./gen_data_sh
	
The output data is written to the ./data directory


To generate charts:
-------------------
While in ./scripts directory, execute the R script r_plot_script.R.

You can do this using Rscript as follows:

	Rscript r_plot_script.R
	
Alternatively, download and install RStudio (an IDE for R) and run 
the script in that.

	




./scripts contains a gen_data.sh which will run the binary and create output files in the ./data directory.
Also contains the R script for generating the charts.

./data contains the raw output from running the binary and piping to a file.

The code was compiled and tested on Linux (gcc 4.8.3).
