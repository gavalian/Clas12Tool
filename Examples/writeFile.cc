//******************************************************************
//*  ██╗  ██╗██╗██████╗  ██████╗     ██╗  ██╗    ██████╗
//*  ██║  ██║██║██╔══██╗██╔═══██╗    ██║  ██║   ██╔═████╗
//*  ███████║██║██████╔╝██║   ██║    ███████║   ██║██╔██║
//*  ██╔══██║██║██╔═══╝ ██║   ██║    ╚════██║   ████╔╝██║
//*  ██║  ██║██║██║     ╚██████╔╝         ██║██╗╚██████╔╝
//*  ╚═╝  ╚═╝╚═╝╚═╝      ╚═════╝          ╚═╝╚═╝ ╚═════╝
//************************ Jefferson National Lab (2017) ***********
//******************************************************************
//* Example program for writing HIPO-4 Files..
//* Includes defining schemas, opening a fil with dictionary
//*--
//* Author: G.Gavalian
//*


#include <iostream>
#include <stdlib.h>
#include "writer.h"

//------------------------------------------------
// function to fill bank with random numbers
void dataFill(hipo::bank &bank);

/**
*  Main Program ........
*/
int main(int argc, char** argv){

    printf("--->>> example program to produce a HIPO file.");
    char outputFile[256];
    sprintf(outputFile,"%s","example_output.hipo");
    //---------------------------------------------------------
    // Define a Schema for particle bank and detector bank
    // Schema constructor takes:
    // name - name of the schema (bank)
    // groupid - a 16 bit number which identifies a group.
    //           this way banks can be grouped in skimming
    // itemid  - and item number (8 bit) to just have a
    //           unique number associated with bank.
    hipo::schema  schemaPart("event::particle",100,1);
    hipo::schema  schemaDet( "event::detector",100,2);
    //---------------------------------------------------------
    // Defining structure of the schema (bank)
    // The columns in the banks (or leafs, if you like ROOT)
    // are given comma separated with type after the name.
    // Available types : I-integer, S-short, B-byte, F-float,
    //                   D-double, L-long
    schemaPart.parse("pid/S,px/F,py/F,pz/F");
    schemaDet.parse("pindex/I,detectorid/I,x/F,y/F,z/F,time/F,energy/F");
    //---------------------------------------------------------
    // Open a writer and register schemas with the writer.
    // The schemas have to be added to the writer before openning
    // the file, since they are written into the header of the file.
    hipo::writer  writer;
    writer.getDictionary().addSchema(schemaPart);
    writer.getDictionary().addSchema(schemaDet);
    writer.open(outputFile);

    hipo::bank partBank(schemaPart,1);
    hipo::bank detBank( schemaDet ,1);


    for(int i = 0; i < 10000; i++){
        int  nparts = 2 + rand()%10;
        int   ndets = 5 + rand()%20;

        printf("particles = %d, detectors = %d\n",nparts, ndets);

    }
    writer.close();
}

void dataFill(hipo::bank &bank){

}
