#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#define TOKEN_VERTEX_POS "v"
#define TOKEN_VERTEX_NOR "vn"
#define TOKEN_VERTEX_TEX "vt"
#define TOKEN_FACE "f"

struct Vector2f {
	float x, y;
};
struct Vector3f {
	float x, y, z;
};

struct ObjMeshVertex {
	Vector3f pos;
	Vector2f texcoord;
	Vector3f normal;
};

/* This is a triangle, that we can render */
struct ObjMeshFace {
	ObjMeshVertex vertices[3];
};

/* This contains a list of triangles */
struct ObjMesh {
	std::vector<ObjMeshFace> faces;
};

/* Internal structure */
struct _ObjMeshFaceIndex {
	int pos_index[3];
	int tex_index[3];
	int nor_index[3];
};

/* Call this function to load a model, only loads triangulated meshes */
ObjMesh LoadObjMesh(std::string filename) {
	ObjMesh myMesh;

	std::vector<Vector3f>           positions;
	std::vector<Vector2f>           texcoords;
	std::vector<Vector3f>           normals;
	std::vector<_ObjMeshFaceIndex>  faces;
	/**
	* Load file, parse it
	* Lines beginning with:
	* '#'  are comments can be ignored
	* 'v'  are vertices positions (3 floats that can be positive or negative)
	* 'vt' are vertices texcoords (2 floats that can be positive or negative)
	* 'vn' are vertices normals   (3 floats that can be positive or negative)
	* 'f'  are faces, 3 values that contain 3 values which are separated by / and <space>
	*/

	std::ifstream filestream;
	filestream.open(filename.c_str());

	std::string line_stream;
	while(std::getline(filestream, line_stream)) {
		std::stringstream str_stream(line_stream);
		std::string type_str;
		str_stream >> type_str;
		if(type_str == TOKEN_VERTEX_POS) {
			Vector3f pos;
			str_stream >> pos.x >> pos.y >> pos.z;
			positions.push_back(pos);
		}
		else if(type_str == TOKEN_VERTEX_TEX) {
			Vector2f tex;
			str_stream >> tex.x >> tex.y;
			texcoords.push_back(tex);
		}
		else if(type_str == TOKEN_VERTEX_NOR) {
			Vector3f nor;
			str_stream >> nor.x >> nor.y >> nor.z;
			normals.push_back(nor);
		}
		else if(type_str == TOKEN_FACE) {
			_ObjMeshFaceIndex face_index;
			char interupt;
			for(int i = 0; i < 3; ++i) {
				str_stream >> face_index.pos_index[i] >> interupt
					>> face_index.tex_index[i] >> interupt
					>> face_index.nor_index[i];
			}
			faces.push_back(face_index);
		}
	}
	// Explicit closing of the file 
	filestream.close();

	for(size_t i = 0; i < faces.size(); ++i) {
		ObjMeshFace face;
		for(size_t j = 0; j < 3; ++j) {
			face.vertices[j].pos = positions[faces[i].pos_index[j] - 1];
			face.vertices[j].texcoord = texcoords[faces[i].tex_index[j] - 1];
			face.vertices[j].normal = normals[faces[i].nor_index[j] - 1];
		}
		myMesh.faces.push_back(face);
	}

	return myMesh;
}

void display(void) {

	ObjMesh mesh = LoadObjMesh("clappy.obj");

	// Begin drawing of triangles.
	glBegin(GL_TRIANGLES);

	// Iterate over each face.
	for(int face_index = 0; face_index < mesh.faces.size(); ++face_index) {
		ObjMeshFace& current_face = mesh.faces[face_index];

		// Each face is a triangle, so draw 3 vertices with their normal
		// and texcoords.
		for(int vertex_index = 0; vertex_index < 3; ++vertex_index) {
			ObjMeshVertex& vertex = current_face.vertices[vertex_index];
			glVertex3f(vertex.pos.x, vertex.pos.y, vertex.pos.z);
			glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);
			glTexCoord2f(vertex.texcoord.x, vertex.texcoord.y);
		}
	}

	// End drawing of triangles.
	glEnd();

}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Homework 6");
	glutDisplayFunc(display);

	glClearColor(0.1f, 0.1f, 0.1f, 0.0f); // background is light gray
	glViewport(0, 0, 1920, 1080);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double winHt = 1.0; // half-height of the window
	glOrtho(-winHt * 64 / 48.0, winHt * 64 / 48.0, -winHt, winHt, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.3, 1.3, 2, 0, 0.25, 0, 0.0, 1.0, 0.0);

	glutMainLoop();
}