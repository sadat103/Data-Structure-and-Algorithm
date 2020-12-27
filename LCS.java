/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package LCS;

import java.util.Scanner;

/**
 *
 * @author Sadat
 */
public class LCS {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        // write your code here
    String strColumn;
    String strRow;

    Scanner sc=new Scanner(System.in);
    System.out.println("Please Enter 2 Strings\n");
    strColumn=sc.nextLine();
    strRow=sc.nextLine();
    int row=strRow.length()+1;
    int col=strColumn.length()+1;

    int C[][]=new int[row][col];
    char[][] direction=new char[row][col];


        for (int i = 1; i <row ; i++) {
            for (int j = 1; j <col ; j++) {
                if(strColumn.charAt(j-1)==strRow.charAt(i-1))
                {
                    C[i][j]=C[i-1][j-1]+1;
                    direction[i][j]='d';
                }
                else
                    {
                        C[i][j]=Integer.max(C[i-1][j],C[i][j-1]);
                        if(C[i][j]==C[i-1][j])
                        	{
                        		direction[i][j]='u';
                        	}
                        else if(C[i][j]==C[i][j-1])
                        	{
                        		direction[i][j]='l';
                        	}

                    }
            }
        }
        int m , n ;
        for(m=1;m<row;m++){
            for(n=1;n<col;n++) {
                System.out.print(C[m][n]+"\t");
               // System.out.print("");
                }
            System.out.println();
        }
        System.out.println();
        int p,q ;
        for(p=1;p<row;p++){
            for(q=1;q<col;q++) {
                System.out.print(direction[p][q]+"\t");
               // System.out.print("");
                }
            System.out.println();
        }
        int i=0,j=0;
        StringBuffer lcs=new StringBuffer();
        for(i=row-1,j=col-1;;)
        {

        
                if(direction[i][j]=='d')
                {
                    //System.out.println("d");
                    lcs.append(strRow.charAt(i-1));
                    i--;
                    j--;
                }
                else if(direction[i][j]=='u')
                {
                    //System.out.println("u" );
                    i--;
                }
                else if(direction[i][j]=='l')
                {
                    //System.out.println("l");
                    j--;
                }

                if(i==0 || j==0)break;


        }
        System.out.println("lcs is : ");
        System.out.println(lcs.reverse());
    }
    
}
