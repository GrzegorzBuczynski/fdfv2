#include <math.h>
#include <stdio.h>

typedef struct
{
    int x, y, z;
} Vector3;

typedef struct
{
	int x, y;
} Point;

Point project(Vector3 vec, Vector3 dir);

Point project(Vector3 vec, Vector3 dir)
{
	
}



Vector3 rotate_vector(Vector3 vector, float rotationMatrix[3][3]);
void rotation_matrix(float rotationMatrix[3][3], int rotX, int rotY, int rotZ);

int main(void)
{
    int rotX;
    int rotY;
    int rotZ;
    Vector3 vector = {0, 0, 1000};
    float rotationMatrix[3][3];

    rotX = 0;
    rotY = 90;
    rotZ = 0;

    printf("%d, %d, %d\n", vector.x, vector.y, vector.z);
    rotation_matrix(rotationMatrix, rotX, rotY, rotZ);
    //vector = rotate_vector(vector, rotationMatrix);

    return 0;
}

void rotation_matrix(float rotationMatrix[3][3], int rotX, int rotY, int rotZ)
{
    float radX, radY, radZ;
    float cosX, sinX, cosY, sinY, cosZ, sinZ;
	Vector3 vector = {0, 0, 1000};

    // Konwersja stopni na radiany
    radX = rotX * M_PI / 180.0;
    radY = rotY * M_PI / 180.0;
    radZ = rotZ * M_PI / 180.0;

    // Obliczenie sinusów i cosinusów
    cosX = cos(radX);
    sinX = sin(radX);
    cosY = cos(radY);
    sinY = sin(radY);
    cosZ = cos(radZ);
    sinZ = sin(radZ);

    // Macierz obrotu łączona
    rotationMatrix[0][0] = cosY * cosZ;
    rotationMatrix[0][1] = -cosY * sinZ;
    rotationMatrix[0][2] = sinY;

    rotationMatrix[1][0] = sinX * sinY * cosZ + cosX * sinZ;
    rotationMatrix[1][1] = -sinX * sinY * sinZ + cosX * cosZ;
    rotationMatrix[1][2] = -sinX * cosY;

    rotationMatrix[2][0] = -cosX * sinY * cosZ + sinX * sinZ;
    rotationMatrix[2][1] = cosX * sinY * sinZ + sinX * cosZ;
    rotationMatrix[2][2] = cosX * cosY;

	// printf("%f, %f \n", rotationMatrix[2][2], rotationMatrix[1][0]);

	rotate_vector(vector, rotationMatrix);
}

Vector3 rotate_vector(Vector3 vector, float rotationMatrix[3][3])
{
    Vector3 rotatedVector;

    // Obliczenie obróconego wektora
    rotatedVector.x = vector.x * rotationMatrix[0][0] + vector.y * rotationMatrix[0][1] + vector.z * rotationMatrix[0][2];
    rotatedVector.y = vector.x * rotationMatrix[1][0] + vector.y * rotationMatrix[1][1] + vector.z * rotationMatrix[1][2];
    rotatedVector.z = vector.x * rotationMatrix[2][0] + vector.y * rotationMatrix[2][1] + vector.z * rotationMatrix[2][2];

	printf("%d, %d, %d \n", rotatedVector.x, rotatedVector.y, rotatedVector.z);

    return rotatedVector;
}






// #include <math.h>
// #include <stdio.h>
// // #define M_PI 3.1416

// typedef struct
// {
// 	int x, y, z;
// }		Vector3;

// Vector3	rotate_vector(Vector3 vector, float *rotationMatrix[3][3]);
// void rotation_matrix(float *rotationMatrix[3][3], int rotX, int rotY, int rotZ);

// int	main(void)
// {
// 	int		rotX;
// 	int		rotY;
// 	int		rotZ;
// 	Vector3	vector = {0, 0, 10};
// 	float	rotationMatrix[3][3];

// 	rotX = 0;
// 	rotY = 0;
// 	rotZ = 45;
// 	rotation_matrix(&rotationMatrix, rotX, rotY, rotZ);
// 	vector = rotate_vector(vector, &rotationMatrix);

// 	printf("%d, %d, %d, \n", vector.x, vector.y, vector.z);
// }

// void rotation_matrix(float	*rotationMatrix[3][3], int rotX, int rotY, int rotZ)
// {
// 	float	radX;
// 	float	radY;
// 	float	radZ;
// 	float	cosX;
// 	float	sinX;
// 	float	cosY;
// 	float	sinY;
// 	float	cosZ;
// 	float	sinZ;

// 	// Konwersja stopni na radiany
// 	radX = rotX * M_PI / 180.0;
// 	radY = rotY * M_PI / 180.0;
// 	radZ = rotZ * M_PI / 180.0;
// 	// Macierze obrotu wokół osi
// 	cosX = cos(radX);
// 	sinX = sin(radX);
// 	cosY = cos(radY);
// 	sinY = sin(radY);
// 	cosZ = cos(radZ);
// 	sinZ = sin(radZ);
// 	// Macierz obrotu łączona
// 	*rotationMatrix[0][0] = cosY * cosZ - sinX * sinY * sinZ;
// 	*rotationMatrix[0][1] = -cosY * sinZ - sinX * cosY * sinZ;
// 	*rotationMatrix[0][1] = cosX * sinZ;

// 	*rotationMatrix[1][0] = sinY * cosZ + cosX	* sinY * sinZ;
// 	*rotationMatrix[1][1] = cosY * cosZ + sinX * sinY * sinZ;
// 	*rotationMatrix[1][1] = sinX * cosZ - cosX	* sinZ;

// 	*rotationMatrix[1][0] = -sinZ * cosY + sinX * cosY * sinZ;
// 	*rotationMatrix[1][1] = -sinZ * sinY - cosX	* cosY * sinZ;
// 	*rotationMatrix[1][1] = cosZ * cosY;
// }

// // Funkcja obliczająca wektor po obrocie
// Vector3	rotate_vector(Vector3 vector, float *rotationMatrix[3][3])
// {
// 	Vector3	rotatedVector;
	

// 	// Obliczenie obróconego wektora
// 	rotatedVector.x = vector.x * *rotationMatrix[0][0] + vector.y
// 		* *rotationMatrix[0][1] + vector.z * *rotationMatrix[0][2];
// 	rotatedVector.y = vector.x * *rotationMatrix[1][0] + vector.y
// 		* *rotationMatrix[1][1] + vector.z * *rotationMatrix[1][2];
// 	rotatedVector.z = vector.x * *rotationMatrix[2][0] + vector.y
// 		* *rotationMatrix[2][1] + vector.z * *rotationMatrix[2][2];
// 	return (rotatedVector);
// }

	// i = 0;
	// rotX = 0;
	// rotY = 0;
	// rotZ = 0;
	// deg = 0.01745329252;
	// while (i <= 180)
	// {
	// 	tab[i] = (int)(cos(i * 0.01745329252));
	// }

// Vector3	rotated_vector(Vector3 v, int **rotationMatrixX)
// {
// 	Vector3	rotatedVector;
// 	rotatedVector.x = v.x * rotationMatrixX[0][0] + v.y * rotationMatrixX[0][1]
// 		+ v.z * rotationMatrixX[0][2];
// 	rotatedVector.y = v.x * rotationMatrixX[1][0] + v.y * rotationMatrixX[1][1]
// 		+ v.z * rotationMatrixX[1][2];
// 	rotatedVector.z = v.x * rotationMatrixX[2][0] + v.y * rotationMatrixX[2][1]
// 		+ v.z * rotationMatrixX[2][2];
// 	return (rotatedVector);
// }

// copilot

// #define M_PI 3.1416

// // Funkcja obliczająca wektor po obrocie
// Vector3 rotated_vector(Vector3 vector, int rotX, int rotY, int rotZ) {
//   // Konwersja stopni na radiany
//   float radX = rotX * M_PI / 180.0;
//   float radY = rotY * M_PI / 180.0;
//   float radZ = rotZ * M_PI / 180.0;

//   // Macierze obrotu wokół osi
//   float cosX = cos(radX);
//   float sinX = sin(radX);
//   float cosY = cos(radY);
//   float sinY = sin(radY);
//   float cosZ = cos(radZ);
//   float sinZ = sin(radZ);

//   // Macierz obrotu łączona
//   float rotationMatrix[3][3] = {
//     { cosY*cosZ, cosZ*sinX*sinY - cosX*sinZ, sinX*sinZ + cosX*cosZ*sinY },
//     { cosY*sinZ, cosX*cosZ + sinX*sinY*sinZ, cosX*sinY*sinZ - cosZ*sinX },
//     { -sinY, cosY*sinX, cosX*cosY }
//   };

//   // Obliczenie obróconego wektora
//   Vector3 rotatedVector;
//   rotatedVector.x = vector.x * rotationMatrix[0][0] + vector.y
	// * rotationMatrix[0][1] + vector.z * rotationMatrix[0][2];
//   rotatedVector.y = vector.x * rotationMatrix[1][0] + vector.y
	// * rotationMatrix[1][1] + vector.z * rotationMatrix[1][2];
//   rotatedVector.z = vector.x * rotationMatrix[2][0] + vector.y
	// * rotationMatrix[2][1] + vector.z * rotationMatrix[2][2];

//   return (rotatedVector);
// }

// Vector3 rotated_vector(Vector3 vector, int rotX, int rotY, int rotZ);

// Vector3	rotatedVector;

// rotatedVector.x = v.x * rotationMatrixX[0][0] + v.y * rotationMatrixX[0][1]
// 	+ v.z * rotationMatrixX[0][2];
// rotatedVector.y = v.x * rotationMatrixX[1][0] + v.y * rotationMatrixX[1][1]
// 	+ v.z * rotationMatrixX[1][2];
// rotatedVector.z = v.x * rotationMatrixX[2][0] + v.y * rotationMatrixX[2][1]
// 	+ v.z * rotationMatrixX[2][2];

// 1 deg =0,01745329252

// 1
// 0,9998476952
// 0,999390827
// 0,9986295348
// 0,9975640503
// 0,9961946981
// 0,9945218954
// 0,9925461516
// 0,9902680687
// 0,9876883406
// 0,984807753
// 0,9816271834
// 0,9781476007
// 0,9743700648
// 0,9702957263
// 0,9659258263
// 0,9612616959
// 0,956304756
// 0,9510565163
// 0,9455185756
// 0,9396926208
// 0,9335804265
// 0,9271838546
// 0,9205048535
// 0,9135454576
// 0,906307787
// 0,8987940463
// 0,8910065242
// 0,8829475929
// 0,8746197071
// 0,8660254038
// 0,8571673007
// 0,8480480962
// 0,8386705679
// 0,8290375726
// 0,8191520443
// 0,8090169944
// 0,79863551
// 0,7880107536
// 0,7771459615
// 0,7660444431
// 0,7547095802
// 0,7431448255
// 0,7313537016
// 0,7193398003
// 0,7071067812
// 0,6946583705
// 0,6819983601
// 0,6691306064
// 0,656059029
// 0,6427876097
// 0,629320391
// 0,6156614753
// 0,6018150232
// 0,5877852523
// 0,5735764364
// 0,5591929035
// 0,544639035
// 0,5299192642
// 0,5150380749
// 0,5
// 0,4848096202
// 0,4694715628
// 0,4539904997
// 0,4383711468
// 0,4226182617
// 0,4067366431
// 0,3907311285
// 0,3746065934
// 0,3583679495
// 0,3420201433
// 0,3255681545
// 0,3090169944
// 0,2923717047
// 0,2756373558
// 0,2588190451
// 0,2419218956
// 0,2249510543
// 0,2079116908
// 0,1908089954
// 0,1736481777
// 0,156434465
// 0,139173101
// 0,1218693434
// 0,1045284633
// 0,08715574275
// 0,06975647374
// 0,05233595624
// 0,0348994967
// 0,01745240644
// 0
// -0,01745240644
// -0,0348994967
// -0,05233595624
// -0,06975647374
// -0,08715574275
// -0,1045284633
// -0,1218693434
// -0,139173101
// -0,156434465
// -0,1736481777
// -0,1908089954
// -0,2079116908
// -0,2249510543
// -0,2419218956
// -0,2588190451
// -0,2756373558
// -0,2923717047
// -0,3090169944
// -0,3255681545
// -0,3420201433
// -0,3583679495
// -0,3746065934
// -0,3907311285
// -0,4067366431
// -0,4226182617
// -0,4383711468
// -0,4539904997
// -0,4694715628
// -0,4848096202
// -0,5
// -0,5150380749
// -0,5299192642
// -0,544639035
// -0,5591929035
// -0,5735764364
// -0,5877852523
// -0,6018150232
// -0,6156614753
// -0,629320391
// -0,6427876097
// -0,656059029
// -0,6691306064
// -0,6819983601
// -0,6946583705
// -0,7071067812
// -0,7193398003
// -0,7313537016
// -0,7431448255
// -0,7547095802
// -0,7660444431
// -0,7771459615
// -0,7880107536
// -0,79863551
// -0,8090169944
// -0,8191520443
// -0,8290375726
// -0,8386705679
// -0,8480480962
// -0,8571673007
// -0,8660254038
// -0,8746197071
// -0,8829475929
// -0,8910065242
// -0,8987940463
// -0,906307787
// -0,9135454576
// -0,9205048535
// -0,9271838546
// -0,9335804265
// -0,9396926208
// -0,9455185756
// -0,9510565163
// -0,956304756
// -0,9612616959
// -0,9659258263
// -0,9702957263
// -0,9743700648
// -0,9781476007
// -0,9816271834
// -0,984807753
// -0,9876883406
// -0,9902680687
// -0,9925461516
// -0,9945218954
// -0,9961946981
// -0,9975640503
// -0,9986295348
// -0,999390827
// -0,9998476952
// -1