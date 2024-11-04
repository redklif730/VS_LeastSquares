#include "Matrix.h"

//Matrix.cpp
Matrix::Matrix(const Matrix& other){
    //cout << "copy constructor used"<<endl;
    m=other.m;
    n=other.n;
    init();
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            matr[i][j]=(other.matr)[i][j];
}
/*Matrix::Matrix(Matrix&& tmp){
    m=tmp.m;
    n=tmp.n;
    matr=tmp.matr;
    tmp.matr=nullptr;
}
*/
Matrix& Matrix::operator=(const Matrix& other){
    //cout << "	operator= used"<<endl;
    if(this != &other){
        //if no match for columns or lines
        if(m!=other.m){
            //cout << "	operator= lines changed"<<endl;
            for(int i=0;i<m;i++)
                delete[] matr[i];
            delete[] matr;
            m=other.m;
            n=other.n;
            init();
        }
        else if(n!=other.n){
            //cout << "	operator= columns changed"<<endl;
            for(int i=0;i<m;i++){
                delete[] matr[i];
                matr[i] = new precision_type[other.n];
            }
            n=other.n;
        }
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++){
                //cout << "line i="<<i<<"	col j="<<j<< "	A[i][j]="<<other.matr[i][j] << endl;
                matr[i][j]=other.matr[i][j];
            }
    }
    return *this;
}


precision_type* Matrix::operator[](int index){
    return matr[index];
}

void Matrix::show(){
    //cout << "Matrix_addr="<<this << "	matr="<<matr<<endl;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)
            //cout << "line i="<<i<<"	col j="<<j<< "	A[i][j]="<<matr[i][j] << endl;
            cout << matr[i][j] << ' ';
        cout << endl;
    }
}

Matrix Matrix::operator+(const Matrix& other){
    //cout << "	operator= used"<<endl;
    if(m==other.m && n==other.n){
        Matrix res(m,n);
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                res[i][j] = matr[i][j]+other.matr[i][j];
        return res;
    }
    else
        cout << "Operator+: Non-equal sizes of matrix"<<endl;
}
Matrix& Matrix::operator+=(const Matrix& other){
    //cout << "	operator= used"<<endl;
    if(m==other.m && n==other.n){
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                matr[i][j]+=other.matr[i][j];
        return *this;
    }
    else
        cout << "Operator+=: Non-equal sizes of matrix"<<endl;
}
Matrix Matrix::operator-(const Matrix& other){
    //cout << "	operator= used"<<endl;
    if(m==other.m && n==other.n){
        Matrix res(m,n);
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                res[i][j] = matr[i][j]-other.matr[i][j];
        return res;
    }
    else
        cout << "Operator-: Non-equal sizes of matrix"<<endl;
}
Matrix& Matrix::operator-=(const Matrix& other){
    //cout << "	operator= used"<<endl;
    if(m==other.m && n==other.n){
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                matr[i][j]-=other.matr[i][j];
        return *this;
    }
    else
        cout << "Operator-=: Non-equal sizes of matrix"<<endl;
}
/*Matrix Matrix::operator+(const Matrix& A, const Matrix& B){
    //cout << "	operator= used"<<endl;
    if(m==other.m && n==other.n){
        Matrix res(m,n);
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                res[i][j] = matr[i][j]+other.matr[i][j];
        return res;
    }
    else
        cout << "Non-equal sizes of matrix"<<endl;
}*/
Matrix Matrix::operator*(const precision_type& num){
    Matrix res(m,n);
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++){
            //cout << "matr[i][j]="<<matr[i][j]<< ' '<<matr[i][j]*num<<endl;
            res[i][j]=matr[i][j]*num;
        }
    return res;
}

Matrix Matrix::operator*(const Matrix& other){
    if(n==other.m){//columns num Matr1=lines num Matr2
        Matrix res(m,other.n);
        for(int i=0;i<m;i++)
            for(int j=0;j<other.n;j++){
                res[i][j]=0;
                for(int k=0;k<n;k++)
                    res[i][j] += matr[i][k]*other.matr[k][j];
            }
        return res;
    }
    else
        cout << "Operator*: Non-matching sizes of matrix"<<endl;
}
//
Matrix& Matrix::operator*=(const Matrix& other){
    if(n==other.m){//columns num Matr1=lines num Matr2
        Matrix res(m,other.n);
        for(int i=0;i<m;i++)
            for(int j=0;j<other.n;j++){
                res[i][j]=0;
                for(int k=0;k<n;k++)
                    res[i][j] += matr[i][k]*other.matr[k][j];
            }
        *this=res;
        return *this;
    }
    else
        cout << "Operator*: Non-matching sizes of matrix"<<endl;
}

//functions
Matrix Matrix::transpose(){
    Matrix res(n,m);
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            res[i][j]=matr[j][i];
    return res;
}

precision_type Matrix::det(){//Minor matrix
    bool zero_elm_diag = false;
    if(n==m){
        precision_type result=1;
        precision_type eps = 1e-12;
        Matrix temp = *this;
        //temp.show();
        //cout << "1*";
        for(int i=0;i<m;i++){
            if(temp[i][i]-eps<0 && temp[i][i]+eps>0 ){
                zero_elm_diag=true;
                for(int k=i+1; k<n && zero_elm_diag;k++){
                    //switching lines
                    if(!(temp[k][i]-eps<0 && temp[k][i]+eps>0)){
                        precision_type *a=temp.matr[k];
                        temp.matr[k]=temp.matr[i];
                        temp.matr[i]=a;
                        zero_elm_diag=false;
                        result*=-1;
                    }
                }
                //cout << "	Switched="<<!zero_elm_diag<<endl;
                //temp.show();
                if(zero_elm_diag)
                    break;
            }
            result*=temp[i][i];
            //cout << temp[i][i] << '*';
            for(int j=n-1;j>=i;j--)
                temp[i][j]/=temp[i][i];//line: 0...01...[possibly not null members]
            for(int k=i+1; k<n;k++){
                if(!(temp[k][i]-eps<0 && temp[k][i]+eps>0)){
                    //cout << temp[k][i] << '*';
                    result*=temp[k][i];
                    for(int j=n-1;j>=i;j--){
                        temp[k][j]/=temp[k][i];
                        temp[k][j]-=temp[i][j];
                    }
                }
            }
            //cout << "Is counted:"<< !zero_elm_diag<<"	det="<<result<<endl;
            //temp.show();
        }
        //cout << endl;
        //temp.show();
        //cout << "Is counted:"<< !zero_elm_diag<<"	det="<<result<<endl;
        return result;
    }
}
Matrix Matrix::inverse(){//minor matrix
    bool zero_elm_diag = false;
    if(n==m){
        //cout << "Matrix to inverse input:"<<endl;
        //(*this).show();
        Matrix res(m,n);
        Matrix tmp(m-1,n-1);
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++){
                for(int a=0;a<m;a++){
                    if(a==i)
                        a++;
                    for(int b=0;b<n && a!=m;b++){
                        if(b==j)
                            b++;
                        if(b!=n){
                            //cout << "matr["<<a<<"]["<<b<<"]=" <<matr[a][b] << endl;
                            //cout << a-1*int(a>i) << ' '<<b-1*int(b>j)<<endl;
                            tmp[a-1*int(a>i)][b-1*int(b>j)] = matr[a][b];
                        }
                    }
                }
                //cout << "A["<<i<<"]["<<j<<"]:"<<endl;
                //tmp.show();
                res[i][j]=tmp.det();
                //cout << "det="<<res[i][j]<<endl;
            }
        //cout <<"Алгебраические дополнения:"<<endl;
        //res.show();
        res=res.transpose();
        precision_type determinant=det();
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++){
                res[i][j]/=determinant;
                if((i+j)%2==1)
                    res[i][j]*=-1;
            }
        //cout<<"Reversed matrix:"<<endl;
        //res.show();

        return res;
    }
}
int matrix_test(){
    cout << string(20,'-')<<"Base Matrix test"<<string(20,'-')<<endl;
    int line = 3, col = 3;
    //init test
    Matrix A(line,col);
    cout << "lines="<<A.lines()<<endl;
    cout << "columnss="<<A.columns()<<endl;
    // [] test
    A[1][2]=2;
    cout << A[1][2]<<endl;
    for(int i=0;i<line;i++)
        for(int j=0;j<col;j++)
            A[i][j]=i*col+j;
    for(int i=0;i<line;i++){
        for(int j=0;j<col;j++)
            cout <<A[i][j]<<' ';
        cout << endl;
    }
    double temp = 90;
    //cout << temp/11<<endl;
    for(int i=0;i<line;i++){
        for(int j=0;j<col;j++)
            cout <<A[i][j]<<' ';
        cout << endl;
    }
    //copy test
    Matrix B = A;
    //A.show();
    cout <<"operator="<<endl;
    //Matrix B(line,col+1);
    B.show();
    //= test
    B = A;
    for(int i=0;i<line;i++){
        for(int j=0;j<col;j++)
            cout <<A[i][j]<<' ';
        cout << endl;
    }
    //+
    Matrix C =B+A;
    C.show();
    //+=
    B+=A;
    B.show();
    //-
    C=C-A;
    C.show();
    //-=
    B-=A;
    B.show();
    C=A+A-B+A-B;//stack of deleting
    C.show();
    cout << "\n\n\nC=A*num"<<endl;
    C=A*2-B;
    C.show();
    C=A*B;
    C.show();
    cout << "\n\n\nComplicated matrix multiply"<<endl;
    //	cout << "Check C destruction"<<endl;
    precision_type arr1[2][3]={{1,2,1},{0,1,2}}, arr2[3][2]={{1,0},{0,1},{1,1}};
    //precision_type** a1=arr1;
    //	A=Matrix(2,3,&(arr1[0][0]));
    //	B=Matrix(3,2,&(arr2[0][0]));
    A=Matrix(2,3);
    B=Matrix(3,2);
    for(int i=0;i<2;i++)
        for(int j=0;j<3;j++)
            A[i][j]=arr1[i][j];
    for(int i=0;i<3;i++)
        for(int j=0;j<2;j++)
            B[i][j]=arr2[i][j];
    A.show();
    B.show();
    C.show();
    C=A*B;
    C.show();
    A.show();
    B.show();

    C=B*A;
    C.show();
    C=C.transpose();
    C.show();
    cout << "\n\n\n"<<string(20,'*')<<"Base Matrix test FINISH"<<string(20,'*')<<endl;

    C[2][2]=4;
    C.det();
    precision_type arr3[3][3]={{15,14,12},{6,7,1},{54,5,7}};
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            C[i][j]=arr3[i][j];
    C.det();
    C.show();
    cout << "\n\n\n next determinant"<<endl;
    precision_type arr4[3][3]={{0,-5,3},{2,-1,9},{-7,4,6}};
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            C[i][j]=arr4[i][j];
    C.show();
    C.det();
    C.show();

    cout << "\n\n\n inverse"<<endl;
    A=C*(C.inverse());
    A.show();
    cout << "\n\n\n inverse"<<endl;
    precision_type arr5[3][3]={{2,5,7},{6,3,4},{5,-2,-3}};
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            C[i][j]=arr5[i][j];
    //	C.show();
    //C.det();
    C.show();
    C.inverse();


    cout << "Matrix 4*4" << endl;
    C = Matrix(4, 4);
    precision_type arr6[4][4] = { {2,5,7,9},{6,3,4,-12},{5,-2,-3, 7},{2,-1,9,12} };
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            C[i][j] = arr6[i][j];
    //	C.show();
        //C.det();

    C.show();
    A = C.inverse();
    A.show();
    Matrix E = C * A;
    E.show();


    return 0;
}
