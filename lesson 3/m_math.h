// Set matrix to identity matrix
void MIdentity(int matrix[16]);

// Matrix multiplication
void MMultiply(int matrix[16], int mul[16], int result[16]);

// Multiply matrix on vector
void MMatrixMultipyVector(const int matrix[16], const int mul[4], int result[4]);

// Multiply vector on matrix
void MVectorMultipyMatrix(const int mul[4], const int matrix[16], int result[4]);

// Create transition matrix
void MTransition(int matrix[16], int FPX, int FPY, int FPZ);

// Create Scale matrix
void MScale(int matrix[16], int FPX, int FPY, int FPZ);

// Create rotation matrices
void MRotationX(int matrix[16], int FPAngle);
void MRotationY(int matrix[16], int FPAngle);
void MRotationZ(int matrix[16], int FPAngle);

// Copy matrices
void MCopy(int source[16], int dest[16]);

// Create perspective matrix
void MPerspective(int matrix[16]);
