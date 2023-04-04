/** EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
 *   Modul               : 
 *   Hari dan Tanggal    :
 *   Nama (NIM)          :
 *   Nama File           : main.c
 *   Deskripsi           : 
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define MAT_SIZE 10

/**
 * @brief fungsi untuk membaca file masukkan dan mengisi matriks
 *
 * @param filename nama file masukkan
 * @param mat matriks yang akan diisi
 */
void readFile(char *filename, int mat[MAT_SIZE][MAT_SIZE])
{
	char buffer[BUFFER_SIZE], *token;
	int i = 0, j = 0;
	FILE *f = fopen(filename, "r");

	while (fgets(buffer, BUFFER_SIZE, f))
	{
		j = 0;
		token = strtok(buffer, ",");
		while (token != NULL)
		{
			mat[i][j] = atoi(token);
			token = strtok(NULL, ",");
			j++;
		}
		i++;
	}
}

/*
Fungsi untuk mengecek apakah elemen berada pada rentang toleransi atau tidak
jika iya, ubah elemen menjadi nol sebagai tanda elemen sudah dicek dan cek elemen di sekitarnya
fungsi berhenti ketika semua elemen di sekitarnya tidak ada lagi yang memenuhi syarat
*/
void cek_kondisi(int mat[MAT_SIZE][MAT_SIZE], int i, int j, int batas_bawah, int batas_atas) {
    //Basis
    if (i < 0 || j < 0 || i > (MAT_SIZE-1) || j > (MAT_SIZE-1) || mat[i][j] < batas_bawah || mat[i][j] > batas_atas){
        return;
    }

    //Rekurens
    if (mat[i][j] >= batas_bawah && mat[i][j] <= batas_atas){
        mat[i][j] = -1;  //menandakan bahwa elemen sudah di cek
        cek_kondisi(mat, i+1, j, batas_bawah, batas_atas);     //cek elemen di bawah
        cek_kondisi(mat, i-1, j, batas_bawah, batas_atas);     //cek elemen di atas
        cek_kondisi(mat, i, j+1, batas_bawah, batas_atas);     //cek elemen di kanan
        cek_kondisi(mat, i, j-1, batas_bawah, batas_atas);     //cek elemen di kiri
        cek_kondisi(mat, i+1, j+1, batas_bawah, batas_atas);   //cek elemen di kanan bawah
        cek_kondisi(mat, i+1, j-1, batas_bawah, batas_atas);   //cek elemen di kiri bawah
        cek_kondisi(mat, i-1, j+1, batas_bawah, batas_atas);   //cek elemen di kanan atas
        cek_kondisi(mat, i-1, j-1, batas_bawah, batas_atas);   //cek elemen di kiri atas
    }
}

//Fungsi untuk menghitung jumlah klaster
int count(int mat[MAT_SIZE][MAT_SIZE], int batas_bawah, int batas_atas) {
    int count = 0;
    for (int i = 0; i < MAT_SIZE; i++){
        for (int j = 0; j < MAT_SIZE; j++){
            if (mat[i][j] >= batas_bawah && mat[i][j] <= batas_atas){
                count++;
                cek_kondisi(mat, i, j, batas_bawah, batas_atas);
            }
        }
    }
    return count;
}

int main()
{
    char filename[100];
    int patokan, toleransi;
    int batas_bawah, batas_atas;
    int mat[MAT_SIZE][MAT_SIZE];

    for (int i = 0; i < MAT_SIZE; i++){
        for (int j = 0; j < MAT_SIZE; j++){
            mat[i][j] = -1;
        }
    }

	// Meminta masukkan
	printf("Masukkan nama file: ");
	scanf("%s", filename);
	printf("Masukkan nilai patokan: ");
	scanf("%d", &patokan);
	printf("Masukkan nilai toleransi: ");
	scanf("%d", &toleransi);

	// Membaca file dan mengisi matriks
	readFile(filename, mat);

	// Menghitung batas bawah dan batas atas
	batas_bawah = patokan-toleransi;
	if (batas_bawah < 0){
        batas_bawah = 0;
	}
	batas_atas = patokan+toleransi;

	// Mencetak jumlah klaster
	printf("Jumlah klaster: %d", count(mat, batas_bawah, batas_atas));

	return 0;
}
