#include<bits/stdc++.h>
using namespace std;

template <typename T>
class vector3d{
private: 
	T x,y,z;
public:
	vector3d(){
		x = y = z = 0;
	}

	vector3d(T x,T y,T z = 0){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	vector3d addition(vector3d vec);
	vector3d substraction(vector3d vec);
	T dot_product(vector3d vec);
	vector3d cross_product(vector3d vec);
	T magnitude();
	vector3d normalization();
	void display();
	T distance(vector3d vec);
	T direction(vector3d B);
	vector3d translation(T tfx,T tfy,T tfz = 0);
	vector3d rotation(T theta,T alpha);
	void scaling(vector3d B, T sfx ,T sfy);
};
template <typename T>
vector3d<T> vector3d<T> ::addition(vector3d<T> vec){
	return vector3d(x+vec.x, y+vec.y, z+vec.z);
}

template <typename T>
vector3d<T> vector3d<T> ::substraction(vector3d<T> vec){
	return vector3d(x-vec.x,y-vec.y,z-vec.z);
}

template <typename T>
T vector3d<T> ::dot_product(vector3d<T> vec){
	return x*vec.x + y*vec.y + z*vec.z;
}

template <typename T>
vector3d<T> vector3d<T> ::cross_product(vector3d vec){
	T x1 = y*vec.z - z*vec.y;
	T y1 = z*vec.x - x*vec.z;
	T z1 = x*vec.y - y*vec.x;
	return vector3d(x1,y1,z1);
}

template <typename T>
T vector3d<T> :: magnitude(){
	return sqrt(x*x + y*y + z*z);
}

template <typename T>
vector3d<T> vector3d<T> :: normalization(){
	if(magnitude() == 0){
		cout<<"Vector's magnitude is zero i.e it can not be normalise"<<endl;
		return vector3d();
	}
	T x1 = x/magnitude();
	T y1 = y/magnitude();
	T z1 = z/magnitude();
	return vector3d(x1,y1,z1);
}

template <typename T>
void vector3d<T> :: display(){
	cout<<"("<< x <<"i,"<< y <<"j,"<< z <<"k)"<<endl;
}

template <typename T>
T vector3d<T> :: distance(vector3d vec){
	vector3d R = this->substraction(vec);
	return R.magnitude();
}

template<typename T>
T vector3d<T> :: direction(vector3d B){
	return acos(this->dot_product(B)/(this->magnitude()*B.magnitude()));
}

template<typename T>
vector3d<T> vector3d<T> :: translation(T tfx,T tfy, T tfz){
	return vector3d(x+tfx,y+tfy,z+tfz);
}

template<typename T>
vector3d<T> vector3d<T> :: rotation(T theta,T alpha){
	T R = sqrt(x*x + y*y);
	T angle = (theta + alpha)*3.14/180;

	T x1 = R*cos(angle);
	T y1 = R*sin(angle);
	return vector3d(x1,y1);
}

template<typename T>
void vector3d<T> :: scaling(vector3d B,T sfx, T sfy){

	 vector3d A1 = vector3d(x*sfx,y*sfy);
	 vector3d B1 = vector3d(B.x*sfx,B.y*sfy);
	 A1.display();
	 B1.display();
}

// Matrix 

template<typename T>
class Matrix{
	T mat[3][3];
public:
	Matrix(){
		mat[2][2] = mat[1][1] = mat[0][0] = 1;
		mat[0][1] = mat[0][2] = mat[1][0] = mat[1][2] = mat[2][0] = mat[2][1] = 0;
	}
	Matrix(T data[]){
		mat[0][0] = data[0];
		mat[0][1] = data[1];
		mat[0][2] = data[2];
		mat[1][0] = data[3];
		mat[1][1] = data[4];
		mat[1][2] = data[5];
		mat[2][0] = data[6];
		mat[2][1] = data[7];
		mat[2][2] = data[8];
	}
	Matrix(T x1,T x2,T x3,T x4,T x5,T x6,T x7,T x8,T x9){
		mat[0][0] = x1;
		mat[0][1] = x2;
		mat[0][2] = x3;
		mat[1][0] = x4;
		mat[1][1] = x5;
		mat[1][2] = x6;
		mat[2][0] = x7;
		mat[2][1] = x8;
		mat[2][2] = x9;	
	}

	Matrix(vector3d<T> row0,vector3d<T> row1,vector3d<T> row2){
		mat[0][0] = row0.x;
		mat[0][1] = row0.y;
		mat[0][2] = row0.z;
		mat[1][0] = row1.x;
		mat[1][1] = row1.y;
		mat[1][2] = row1.z;
		mat[2][0] = row2.x;
		mat[2][1] = row2.y;
		mat[2][2] = row2.z;		
	}

	Matrix identify(){
		return Matrix(1,0,0,0,1,0,0,0,1);
	}

	Matrix zero(){
		return Matrix(0,0,0,0,0,0,0,0,0);
	}

	Matrix one(){
		return Matrix(1,1,1,1,1,1,1,1,1);
	}

	T determinate(){
		T v1 = mat[0][0] * (mat[2][2] * mat[1][1] -
        	mat[2][1] * mat[1][2]);
    	T v2 = mat[1][0] * (mat[2][2] * mat[0][1] -
        	mat[2][1] * mat[0][2]);
    	T v3 = mat[2][0] * (mat[1][2] * mat[0][1] -
        	mat[1][1] * mat[0][2]);
    	return v1 - v2 + v3;
	}

	Matrix adjacency(){
		Matrix a;
	    a.mat[0][0] = mat[2][2] * mat[1][1] - mat[2][1] * mat[1][2];
	    a.mat[0][1] = mat[2][1] * mat[0][2] - mat[2][2] * mat[0][1];
	    a.mat[0][2] = mat[1][2] * mat[0][1] - mat[1][1] * mat[0][2];
	    a.mat[1][0] = mat[2][0] * mat[1][2] - mat[2][2] * mat[1][0];
	    a.mat[1][1] = mat[2][2] * mat[0][0] - mat[2][0] * mat[0][2];
	    a.mat[1][2] = mat[1][0] * mat[0][2] - mat[1][2] * mat[0][0];
	    a.mat[2][0] = mat[2][1] * mat[1][0] - mat[2][0] * mat[1][1];
	    a.mat[2][1] = mat[2][0] * mat[0][1] - mat[2][1] * mat[0][0];
	    a.mat[2][2] = mat[1][1] * mat[0][0] - mat[1][0] * mat[0][1];
	    return a;
	}
	Matrix inverse(){
		
	    return this->adjacency().multiply(1 / this->determinate());
	}

	Matrix transpose(){
		Matrix a;
		a.mat[0][0] = mat[0][0];
		a.mat[0][1] = mat[0][1];
		a.mat[0][2] = mat[0][2];
		a.mat[1][0] = mat[1][0];
		a.mat[1][1] = mat[1][1];
		a.mat[1][2] = mat[1][2];
		a.mat[2][0] = mat[2][0];
		a.mat[2][1] = mat[2][1];
		a.mat[2][2] = mat[2][2];
		swap(a.mat[0][1],a.mat[1][0]);
		swap(a.mat[0][2],a.mat[2][0]);
		swap(a.mat[1][2],a.mat[2][1]);
		return a;
	}

	Matrix add(T x){
		Matrix a;
		a.mat[0][0] = mat[0][0] + x;
		a.mat[0][1] = mat[0][1] + x;
		a.mat[0][2] = mat[0][2] + x;
		a.mat[1][0] = mat[1][0] + x;
		a.mat[1][1] = mat[1][1] + x;
		a.mat[1][2] = mat[1][2] + x;
		a.mat[2][0] = mat[2][0] + x;
		a.mat[2][1] = mat[2][1] + x;
		a.mat[2][2] = mat[2][2] + x;
		return a;
	}

	Matrix subtract(T x){
		Matrix a;
		a.mat[0][0] = mat[0][0] - x;
		a.mat[0][1] = mat[0][1] - x;
		a.mat[0][2] = mat[0][2] - x;
		a.mat[1][0] = mat[1][0] - x;
		a.mat[1][1] = mat[1][1] - x;
		a.mat[1][2] = mat[1][2] - x;
		a.mat[2][0] = mat[2][0] - x;
		a.mat[2][1] = mat[2][1] - x;
		a.mat[2][2] = mat[2][2] - x;
		return a;
	}

	Matrix multiply(T x){
		Matrix a;
		a.mat[0][0] = mat[0][0] * x;
		a.mat[0][1] = mat[0][1] * x;
		a.mat[0][2] = mat[0][2] * x;
		a.mat[1][0] = mat[1][0] * x;
		a.mat[1][1] = mat[1][1] * x;
		a.mat[1][2] = mat[1][2] * x;
		a.mat[2][0] = mat[2][0] * x;
		a.mat[2][1] = mat[2][1] * x;
		a.mat[2][2] = mat[2][2] * x;
		return a;
	}

	Matrix divide(T x){
		Matrix a;
		a.mat[0][0] = mat[0][0] / x;
		a.mat[0][1] = mat[0][1] / x;
		a.mat[0][2] = mat[0][2] / x;
		a.mat[1][0] = mat[1][0] / x;
		a.mat[1][1] = mat[1][1] / x;
		a.mat[1][2] = mat[1][2] / x;
		a.mat[2][0] = mat[2][0] / x;
		a.mat[2][1] = mat[2][1] / x;
		a.mat[2][2] = mat[2][2] / x;
		return a;
	}

	Matrix add(Matrix<T> rhs){
		Matrix a;
		a.mat[0][0] = mat[0][0] + rhs.mat[0][0];
		a.mat[0][1] = mat[0][1] + rhs.mat[0][1]; 
		a.mat[0][2] = mat[0][2] + rhs.mat[0][2];
	    a.mat[1][0] = mat[1][0] + rhs.mat[1][0]; 
	    a.mat[1][1] = mat[1][1] + rhs.mat[1][1]; 
	    a.mat[1][2] = mat[1][2] + rhs.mat[1][2];
	    a.mat[2][0] = mat[2][0] + rhs.mat[2][0]; 
	    a.mat[2][1] = mat[2][1] + rhs.mat[2][1]; 
	    a.mat[2][2] = mat[2][2] + rhs.mat[2][2];
	    return a;
	}

	Matrix subtract(Matrix<T> rhs){
		Matrix a;
		a.mat[0][0] = mat[0][0] - rhs.mat[0][0];
		a.mat[0][1] = mat[0][1] - rhs.mat[0][1]; 
		a.mat[0][2] = mat[0][2] - rhs.mat[0][2];
	    a.mat[1][0] = mat[1][0] - rhs.mat[1][0]; 
	    a.mat[1][1] = mat[1][1] - rhs.mat[1][1]; 
	    a.mat[1][2] = mat[1][2] - rhs.mat[1][2];
	    a.mat[2][0] = mat[2][0] - rhs.mat[2][0]; 
	    a.mat[2][1] = mat[2][1] - rhs.mat[2][1]; 
	    a.mat[2][2] = mat[2][2] - rhs.mat[2][2];
	    return a;
	}

	Matrix multiply(Matrix<T> rhs){
		Matrix m;
	    m.mat[0][0] = mat[0][0] * rhs.mat[0][0] + mat[0][1] * rhs.mat[1][0] + mat[0][2] * rhs.mat[2][0];
	    m.mat[0][1] = mat[0][0] * rhs.mat[0][1] + mat[0][1] * rhs.mat[1][1] + mat[0][2] * rhs.mat[2][1];
	    m.mat[0][2] = mat[0][0] * rhs.mat[0][2] + mat[0][1] * rhs.mat[1][2] + mat[0][2] * rhs.mat[2][2];
	    m.mat[1][0] = mat[1][0] * rhs.mat[0][0] + mat[1][1] * rhs.mat[1][0] + mat[1][2] * rhs.mat[2][0];
	    m.mat[1][1] = mat[1][0] * rhs.mat[0][1] + mat[1][1] * rhs.mat[1][1] + mat[1][2] * rhs.mat[2][1];
	    m.mat[1][2] = mat[1][0] * rhs.mat[0][2] + mat[1][1] * rhs.mat[1][2] + mat[1][2] * rhs.mat[2][2];
	    m.mat[2][0] = mat[2][0] * rhs.mat[0][0] + mat[2][1] * rhs.mat[1][0] + mat[2][2] * rhs.mat[2][0];
	    m.mat[2][1] = mat[2][0] * rhs.mat[0][1] + mat[2][1] * rhs.mat[1][1] + mat[2][2] * rhs.mat[2][1];
	    m.mat[2][2] = mat[2][0] * rhs.mat[0][2] + mat[2][1] * rhs.mat[1][2] + mat[2][2] * rhs.mat[2][2];
	    return m;
	}

	void display(){
		cout<<mat[0][0]<<" "<<mat[0][1]<<" "<<mat[0][2]<<endl;
		cout<<mat[1][0]<<" "<<mat[1][1]<<" "<<mat[1][2]<<endl;
		cout<<mat[2][0]<<" "<<mat[2][1]<<" "<<mat[2][2]<<endl;
		cout<<endl;
	}
};
int main(){
	// cout<<"Enter the components of the vector in the form of ai + bj+ ck\n";
	// cout<<"For vector A : ";
	float x,y,z;
	cin>>x>>y>>z;
	vector3d<float> A(x,y,z);
	// cout<<"For vector B : ";
	cin>>x>>y>>z;
	vector3d<float> B(x,y,z);
	vector3d<float> R = A.addition(B);
	R.display();

	vector3d<float> R1 = A.substraction(B);
	R1.display();

	float d = A.dot_product(B);
	cout<<d<<endl;

	vector3d<float> R2 = A.cross_product(B);
	R2.display();

	cout<<A.magnitude()<<endl;
	cout<<B.magnitude()<<endl;

	vector3d<float> n = A.normalization();
	n.display();
	cout<<n.magnitude()<<endl;

	cout<<A.distance(B)<<endl;

	cout<<A.direction(B)<<" rad"<<endl;

	vector3d<float> T = A.translation(2 ,3, 4);
	T.display();

	vector3d<float> S = A.rotation(45,45);
	S.display();

	A.scaling(B,2,3);
	//---------------------------------------------------
	// Matrix
	float data[9];
	for(int i=0;i<9;i++){
		cin>>data[i];
	}
	Matrix<float> m(data);
	//determinate..
	cout<<"Determinate : "<<m.determinate()<<endl;
	//Transpose
	cout<<"Transpose of given matrix"<<endl;
	Matrix<float> transpose = m.transpose();
	transpose.display();

	//Adjacency
	cout<<"Adjacency of given matrix"<<endl;
	Matrix<float> adjacency = m.adjacency();
	adjacency.display();

	//Inverse
	cout<<"Inverse of given matrix"<<endl;
	Matrix<float> inverse = m.inverse();
	inverse.display();

	//Addition of two matrix
	for(int i=0;i<9;i++) cin>>data[i];
	cout<<"Addition of two matrix"<<endl;

	Matrix<float> n1(data);
	Matrix<float> add = m.add(n1);
	add.display();

	cout<<"substraction of two matrix"<<endl;
	Matrix<float> sub = m.subtract(n1);
	sub.display();

	cout<<"Multiplication of two matrix"<<endl;
	Matrix<float> mul = m.multiply(n1);
	mul.display();
	return 0;
}
