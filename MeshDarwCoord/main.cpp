///圆柱mesh画
#include <iostream>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include<cmath>
#define pi 3.1415926
using namespace std;
typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;
void DrawZCoord(int n, int count, int k, double ArixLength, double r_circle, float ArrowLength, string filename);
void DrawYCoord(int n, int count, int k, double ArixLength, double r_circle, float ArrowLength, string filename);
void DrawXCoord(int n, int count, int k, double ArixLength, double r_circle, float ArrowLength, string filename);

int main()
{
	
	int n = 4, count = 10000, k = -1;
	//int ArixLength = 30;
	//double r_circle = 0.3;
	//float ArrowLength = ArixLength + 0.8;
	//DrawZCoord(n,count, k, ArixLength, r_circle, ArrowLength, "Z");
	//DrawYCoord(n, count, k, ArixLength, r_circle, ArrowLength, "Y");
	//DrawXCoord(n, count, k, ArixLength, r_circle, ArrowLength, "X");

	float ArixLength = 0.15;
	double r_circle = 30;
	float ArrowLength = ArixLength + 0.8;
	DrawZCoord(n, count, k, ArixLength, r_circle, ArrowLength, "XOY");
	DrawYCoord(n, count, k, ArixLength, r_circle, ArrowLength, "XOZ");
	DrawXCoord(n, count, k, ArixLength, r_circle, ArrowLength, "YOZ"); 

}
void DrawZCoord(int n, int count, int k, double ArixLength, double r_circle, float ArrowLength, string filename)
{
	MyMesh meshZ;
	MyMesh::VertexHandle* vhandleZ = new MyMesh::VertexHandle[count];
	std::vector<MyMesh::VertexHandle>face_vhandles;
	for (int j = 0; j < 2; j++) {
		double distance = ArixLength * sin(j * pi / 2);// 原先是 sin

		for (int i = 0; i < n; i++) {
			++k;
			float po = r_circle * cos(2 * i * pi / n);
			float p1 = r_circle * sin(2 * i * pi / n);
			vhandleZ[k] = meshZ.add_vertex(MyMesh::Point(r_circle * cos(2 * i * pi / n), r_circle * sin(2 * i * pi / n), distance));
			// 对网格添加顶点
		}
	}
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < n; j++) {
			int topRight = i * n + j;
			int topLeft = i * n + (j + 1) % n;
			int bottomRight = (i + 1) * n + j;
			int bottomLeft = (i + 1) * n + (j + 1) % n;
			face_vhandles.clear();
			face_vhandles.push_back(vhandleZ[bottomRight]);
			face_vhandles.push_back(vhandleZ[bottomLeft]);
			face_vhandles.push_back(vhandleZ[topRight]);
			meshZ.add_face(face_vhandles);

			face_vhandles.clear();
			face_vhandles.push_back(vhandleZ[bottomLeft]);
			face_vhandles.push_back(vhandleZ[topLeft]);
			face_vhandles.push_back(vhandleZ[topRight]);
			meshZ.add_face(face_vhandles);

		}
	}

	vhandleZ[k + 1] = meshZ.add_vertex(MyMesh::Point(0, 0, ArrowLength));
	for (int i = 0; i < n; i++)
	{
		face_vhandles.clear();
		face_vhandles.push_back(vhandleZ[k - i]);
		face_vhandles.push_back(vhandleZ[k - (i + 1) % n]);
		face_vhandles.push_back(vhandleZ[k + 1]);


		meshZ.add_face(face_vhandles);
	}
	try
	{

		if (!OpenMesh::IO::write_mesh(meshZ,filename + " .obj")) {
			std::cerr << "Cannot write mesh to file ' output5 .off ' " << std::endl;
			
		}

	}
	catch (std::exception & x) {
		std::cerr << x.what() << std::endl;
		
	}

}
void DrawYCoord(int n, int count, int k, double ArixLength, double r_circle, float ArrowLength, string filename)
{
	MyMesh meshY;
	MyMesh::VertexHandle* vhandleY = new MyMesh::VertexHandle[count];
	std::vector<MyMesh::VertexHandle>face_vhandles;
	for (int j = 0; j < 2; j++) {
		double distance = ArixLength * sin(j * pi / 2);// 原先是 sin

		for (int i = 0; i < n; i++) {
			++k;
			float po = r_circle * cos(2 * i * pi / n);
			float p1 = r_circle * sin(2 * i * pi / n);
			vhandleY[k] = meshY.add_vertex(MyMesh::Point(r_circle * cos(2 * i * pi / n), distance, r_circle * sin(2 * i * pi / n)));
			// 对网格添加顶点
		}
	}
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < n; j++) {
			int topRight = i * n + j;
			int topLeft = i * n + (j + 1) % n;
			int bottomRight = (i + 1) * n + j;
			int bottomLeft = (i + 1) * n + (j + 1) % n;
			face_vhandles.clear();
			face_vhandles.push_back(vhandleY[bottomRight]);
			face_vhandles.push_back(vhandleY[bottomLeft]);
			face_vhandles.push_back(vhandleY[topRight]);
			meshY.add_face(face_vhandles);

			face_vhandles.clear();
			face_vhandles.push_back(vhandleY[bottomLeft]);
			face_vhandles.push_back(vhandleY[topLeft]);
			face_vhandles.push_back(vhandleY[topRight]);
			meshY.add_face(face_vhandles);

		}
	}

	vhandleY[k + 1] = meshY.add_vertex(MyMesh::Point(0,ArrowLength, 0));
	for (int i = 0; i < n; i++)
	{
		face_vhandles.clear();
		face_vhandles.push_back(vhandleY[k - i]);
		face_vhandles.push_back(vhandleY[k - (i + 1) % n]);
		face_vhandles.push_back(vhandleY[k + 1]);
		meshY.add_face(face_vhandles);
	}
	try
	{

		if (!OpenMesh::IO::write_mesh(meshY, filename + " .obj")) {
			std::cerr << "Cannot write mesh to file ' output5 .off ' " << std::endl;

		}

	}
	catch (std::exception & x) {
		std::cerr << x.what() << std::endl;

	}

}
void DrawXCoord(int n, int count, int k, double ArixLength, double r_circle, float ArrowLength, string filename)
{
	MyMesh meshX;
	MyMesh::VertexHandle* vhandleX = new MyMesh::VertexHandle[count];
	std::vector<MyMesh::VertexHandle>face_vhandles;
	for (int j = 0; j < 2; j++) {
		double distance = ArixLength * sin(j * pi / 2);// 原先是 sin

		for (int i = 0; i < n; i++) {
			++k;
			float po = r_circle * cos(2 * i * pi / n);
			float p1 = r_circle * sin(2 * i * pi / n);
			vhandleX[k] = meshX.add_vertex(MyMesh::Point(distance, r_circle * cos(2 * i * pi / n), r_circle * sin(2 * i * pi / n)));
			// 对网格添加顶点
		}
	}
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < n; j++) {
			int topRight = i * n + j;
			int topLeft = i * n + (j + 1) % n;
			int bottomRight = (i + 1) * n + j;
			int bottomLeft = (i + 1) * n + (j + 1) % n;
			face_vhandles.clear();
			face_vhandles.push_back(vhandleX[bottomRight]);
			face_vhandles.push_back(vhandleX[bottomLeft]);
			face_vhandles.push_back(vhandleX[topRight]);
			meshX.add_face(face_vhandles);

			face_vhandles.clear();
			face_vhandles.push_back(vhandleX[bottomLeft]);
			face_vhandles.push_back(vhandleX[topLeft]);
			face_vhandles.push_back(vhandleX[topRight]);
			meshX.add_face(face_vhandles);

		}
	}

	vhandleX[k + 1] = meshX.add_vertex(MyMesh::Point(ArrowLength,0, 0));
	for (int i = 0; i < n; i++)
	{
		face_vhandles.clear();
		face_vhandles.push_back(vhandleX[k - i]);
		face_vhandles.push_back(vhandleX[k - (i + 1) % n]);
		face_vhandles.push_back(vhandleX[k + 1]);
		meshX.add_face(face_vhandles);
	}
	try
	{

		if (!OpenMesh::IO::write_mesh(meshX, filename + " .obj")) {
			std::cerr << "Cannot write mesh to file ' output5 .off ' " << std::endl;

		}

	}
	catch (std::exception & x) {
		std::cerr << x.what() << std::endl;

	}

}


//
//// 生成球  n 最好输入偶数  10 或者 100 
//#include <iostream>
//#include <OpenMesh/Core/IO/MeshIO.hh>
//#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
//#include<cmath>
//#define pi 3.1415926
//using namespace std;
//typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;
//
//int main()
//{
//    MyMesh mesh;
//    int n, count = 10000, k = -1;
//    cout << "n:";
//    cin >> n;
//    MyMesh::VertexHandle* vhandle = new MyMesh::VertexHandle[count];
//    std::vector<MyMesh::VertexHandle>face_vhandles;
//    for (int j = 0; j < n; j++) {
//        double distance = cos(j * pi / n);// 原先是 sin
//        double r_circle = sin(j * pi / n);
//        for (int i = 0; i < n; i++) {
//            ++k;
//            vhandle[k] = mesh.add_vertex(MyMesh::Point(r_circle * cos(2 * i * pi / n), r_circle * sin(2 * i * pi / n), distance));
//            // 对网格添加顶点
//        }
//    }
//    for (int i = 0; i < n - 1; i++) {
//        for (int j = 0; j < n; j++) {
//            int topRight = i * n + j;
//            int topLeft = i * n + (j + 1) % n;
//            int bottomRight = (i + 1) * n + j;
//            int bottomLeft = (i + 1) * n + (j + 1) % n;
//            face_vhandles.clear();
//            face_vhandles.push_back(vhandle[bottomRight]);
//            face_vhandles.push_back(vhandle[bottomLeft]);
//            face_vhandles.push_back(vhandle[topRight]);
//            mesh.add_face(face_vhandles);
//
//            face_vhandles.clear();
//            face_vhandles.push_back(vhandle[bottomLeft]);
//            face_vhandles.push_back(vhandle[topLeft]);
//            face_vhandles.push_back(vhandle[topRight]);
//            mesh.add_face(face_vhandles);
//
//        }
//    }
//    vhandle[k + 1] = mesh.add_vertex(MyMesh::Point(0, 0, -1));
//    for (int i = 0; i < n; i++) 
//    {
//        face_vhandles.clear();
//        face_vhandles.push_back(vhandle[k - i]);
//        face_vhandles.push_back(vhandle[k - (i + 1) % n]);
//        face_vhandles.push_back(vhandle[k + 1]);
//        mesh.add_face(face_vhandles);
//    }
//    try
//    {
//        if (!OpenMesh::IO::write_mesh(mesh, "output5 .off")) {
//            std::cerr << "Cannot write mesh to file ' output5 .off ' " << std::endl;
//            return 1;
//        }
//    }
//    catch (std::exception & x) {
//        std::cerr << x.what() << std::endl;
//        return 1;
//    }
//    return 0;
//}