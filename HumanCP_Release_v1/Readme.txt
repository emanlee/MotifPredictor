
This program (named motifpredictor) is used to identify motifs (miRNA-TF-gene loops) from networks

=======================
INSTALLATION & USAGE

Pre-requisite:
1. Linux/Mac
2. C/C++ compiler (i.e. gcc, g++, dev c++)


Steps:
1. Download codes and data files 

2. Compile motifpredictor

For Linux/Mac
 LANG=C gcc -Wall get_model_composite.c  -o get_model_composite
 LANG=C gcc -Wall get_model_miRNA.c  -o get_model_miRNA
 LANG=C gcc -Wall get_model_TF.c  -o get_model_TF



3. Run samples

For Linux/Mac

./get_model_TF  \
-input_TF2miRNA   humanCP.TF2miRNA.txt \
-input_TF2gene    humanCP.TF2gene.txt    \
-input_miRNA2TF   humanCP.miRNA2TF.txt   \
-input_miRNA2gene humanCP.miRNA2gene.txt  \
-output_file      humanCP.TF_motif.txt

./get_model_miRNA  \
-input_TF2miRNA   humanCP.TF2miRNA.txt \
-input_TF2gene    humanCP.TF2gene.txt    \
-input_miRNA2TF   humanCP.miRNA2TF.txt   \
-input_miRNA2gene humanCP.miRNA2gene.txt  \
-output_file      humanCP.miRNA_motif.txt

./get_model_composite  \
-input_TF2miRNA   humanCP.TF2miRNA.txt \
-input_TF2gene    humanCP.TF2gene.txt    \
-input_miRNA2TF   humanCP.miRNA2TF.txt   \
-input_miRNA2gene humanCP.miRNA2gene.txt  \
-output_file      humanCP.composite_motif.txt




=======================
Contact Us

Dr Zhongming Zhao, 
Center for Precision Health, 
School of Biomedical Informatics, 
The University of Texas Health Science Center at Houston, 
7000 Fannin Street, Houston, TX 77030, USA 
E-mail: zhongming.zhao@uth.tmc.edu
 

=======================