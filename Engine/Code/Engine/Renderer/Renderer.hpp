#pragma once
#include <string>
#include "Engine/Renderer/RGBA.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Vector4.hpp"
#include "Engine/Math/Matrix4x4.hpp"
#include "Engine/Math/MatrixStack4x4.hpp"

//-----------------------------------------------------------------------------------------------
#define UNUSED(x) (void)(x);

//---------------------------------------------------------------------------------
// FIXMEs / TODOs / NOTE macros from http://www.flipcode.com/archives/FIXME_TODO_Notes_As_Warnings_In_Compiler_Output.shtml
#define _QUOTE(x) # x
#define QUOTE(x) _QUOTE(x)
#define __FILE__LINE__ __FILE__ "(" QUOTE(__LINE__) ") : "

#define NOTE( x )  message( x )
#define FILE_LINE  message( __FILE__LINE__ )

#define TODO( x )  message( __FILE__LINE__"\n"           \
        " ------------------------------------------------\n" \
        "|  TODO :   " #x "\n" \
        " -------------------------------------------------\n" )
#define FIXME( x )  message(  __FILE__LINE__"\n"           \
        " ------------------------------------------------\n" \
        "|  FIXME :  " #x "\n" \
        " -------------------------------------------------\n" )
#define todo( x )  message( __FILE__LINE__" TODO :   " #x "\n" ) 
#define fixme( x )  message( __FILE__LINE__" FIXME:   " #x "\n" ) 

//-----------------------------------------------------------------------------------
#define CHECK_GL_ERRORS
#ifdef CHECK_GL_ERRORS
    #define GL_CHECK_ERROR()  Renderer::GLCheckError(__FILE__, __LINE__);
#endif


//-----------------------------------------------------------------------------------
class AABB2;
class AABB3;
class Texture;
class Face;
class BitmapFont;
class ShaderProgram;
class Material;
class Framebuffer;
struct Vertex_PCT;
struct Vertex_PCUTB;


class Renderer
{
public:
	//ENUMS//////////////////////////////////////////////////////////////////////////
	enum class DrawMode : unsigned int
	{
		QUADS,
		QUAD_STRIP,
		POINTS,
		LINES,
		LINE_LOOP,
		POLYGON,
		TRIANGLES,
		NUM_DRAW_MODES
	};

    //TYPEDEFS//////////////////////////////////////////////////////////////////////////
    typedef unsigned int GLuint;
    typedef int GLint;
    typedef int GLsizei;
    typedef unsigned int GLenum;
    typedef bool GLboolean;


    //CONSTRUCTORS//////////////////////////////////////////////////////////////////////////
    Renderer();
    ~Renderer();

    //FUNCTIONS//////////////////////////////////////////////////////////////////////////
    void ClearScreen(float red, float green, float blue);
    void ClearScreen(const RGBA& color);
    void PushMatrix();
    void PopMatrix();
    void Translate(float x, float y, float z);
    void Translate(const Vector2& xy);
    void Translate(const Vector3& xyz);
    void Rotate(float rotationDegrees);
    void Rotate(float rotationDegrees, float x, float y, float z);
    void Scale(float x, float y, float z);
    unsigned char GetDrawMode(DrawMode mode) const;

    //STATE MODIFICATION//////////////////////////////////////////////////////////////////////////
    void EnableAdditiveBlending();
    void EnableAlphaBlending();
    void EnableInvertedBlending();
    void EnableDepthTest(bool enabled);
    void EnableFaceCulling(bool enabled);
    void BindTexture(const Texture& texture);
    void UnbindTexture();
    void SetOrtho(const Vector2& bottomLeft, const Vector2& topRight);
	void BeginOrtho(const Vector2& bottomLeft, const Vector2& topRight);
	void EndOrtho();
	void SetPerspective(float fovDegreesY, float aspect, float nearDist, float farDist);
	void BeginPerspective(float fovDegreesY, float aspect, float nearDist, float farDist);
	void EndPerspective();
	void SetColor(float red, float green, float blue, float alpha);
    void SetColor(const RGBA& color);
    void SetPointSize(float size);
    void SetLineWidth(float width);

    //BUFFERS//////////////////////////////////////////////////////////////////////////
    int GenerateBufferID();
    void DeleteBuffers(int vboID);
    void BindAndBufferVBOData(int vboID, const Vertex_PCT* vertexes, int numVerts);
    void BindAndBufferVBOData(int vboID, const Vertex_PCUTB* vertexes, int numVerts);
	void DrawVertexArrayModern(const Vertex_PCT* vertexes, int numVertexes, DrawMode drawMode /*= QUADS*/, Texture* texture /*= nullptr*/);
	void DrawVertexArray(const Vertex_PCT* vertexes, int numVertexes, DrawMode drawMode = DrawMode::QUADS, Texture* texture = nullptr);
    void DrawVBO_PCT(unsigned int vboID, int numVerts, DrawMode drawMode = DrawMode::QUADS, Texture* texture = nullptr);
    void DrawVBO_PCUTB(unsigned int vboID, int numVerts, DrawMode drawMode = DrawMode::QUADS, Texture* texture = nullptr);

    //DRAWING//////////////////////////////////////////////////////////////////////////
    void DrawPoint(const Vector2& point, const RGBA& color = RGBA::WHITE, float pointSize = 1.0f);
    void DrawPoint(const Vector3& point, const RGBA& color = RGBA::WHITE, float pointSize = 1.0f);
    void DrawPoint(float x, float y, const RGBA& color = RGBA::WHITE, float pointSize = 1.0f);
    void DrawLine(const Vector2& start, const Vector2& end, const RGBA& color = RGBA::WHITE, float lineThickness = 1.0f);
    void DrawLine(const Vector3& start, const Vector3& end, const RGBA& color = RGBA::WHITE, float lineThickness = 1.0f);
    void DrawAABB(const AABB2& bounds, const RGBA& color = RGBA::WHITE);
    void DrawAABB(const AABB3& bounds, const RGBA& color = RGBA::WHITE);
    void DrawAABBBoundingBox(const AABB3& bounds, const RGBA& color = RGBA::WHITE);
    void DrawTexturedAABB3(const AABB3& bounds, const RGBA& color = RGBA::WHITE, const Vector2& texCoordMins = Vector2::ZERO, const Vector2& texCoordMaxs = Vector2::ONE, Texture* texture = nullptr);
    void DrawTexturedAABB(const AABB2& bounds, const Vector2& texCoordMins, const Vector2& texCoordMaxs, Texture* texture = nullptr, const RGBA& color = RGBA::WHITE);
    void DrawTexturedFace(const Face& face, const Vector2& texCoordMins, const Vector2& texCoordMaxs, Texture* texture = nullptr, const RGBA& color = RGBA::WHITE);
    void BindFramebuffer(Framebuffer* fbo);
    void FrameBufferCopyToBack(Framebuffer* fbo);
    void DrawPolygonOutline(const Vector2& center, float radius, int numSides, float radianOffset, const RGBA& color = RGBA::WHITE);
    void DrawPolygon(const Vector2& center, float radius, int numSides, float radianOffset, const RGBA& color = RGBA::WHITE);
    void DrawText2D(const Vector2& startBottomLeft, const std::string& asciiText, float cellWidth, float cellHeight, const RGBA& tint = RGBA::WHITE, bool drawShadow = false, const BitmapFont* font = nullptr);
    void DrawText2D(const Vector2& position, const std::string& asciiText, float scale, const RGBA& tint = RGBA::WHITE, bool drawShadow = false, const BitmapFont* font = nullptr, const Vector2& right = Vector2::UNIT_X, const Vector2& up = Vector2::UNIT_Y);

    //MODERN RENDERING (AKA: ORGANIZE THESE LATER)//////////////////////////////////////////////////////////////////////////
    static void GLCheckError(const char* file, size_t line);
    void BindMeshToVAOVertexPCT(GLuint vao, GLuint vbo, GLuint ibo, ShaderProgram* program);
    void UnbindIbo();
    void BindMeshToVAOVertexPCUTB(GLuint vao, GLuint vbo, GLuint ibo, ShaderProgram* program);
    void RenderBufferDestroy(GLuint buffer);                                    
    GLuint GenerateVAOHandle();
    GLuint RenderBufferCreate(void* data, size_t count, size_t elementSize, GLenum usage/* = GL_STATIC_DRAW*/);
    int CreateSampler(GLenum min_filter, GLenum magFilter, GLenum uWrap, GLenum vWrap);
    inline void PushProjection(const Matrix4x4& proj) { m_projStack.Push(proj); };
    inline void PushView(const Matrix4x4& view) { m_viewStack.Push(view); };
    inline void PopProjection() { m_projStack.Pop(); };
    inline void PopView() { m_viewStack.Pop(); };
    inline Matrix4x4 GetProjection() { return m_projStack.GetTop(); };
    inline Matrix4x4 GetView() { return m_viewStack.GetTop(); };
	void RotateView(float degrees, const Vector3& axis);
	void TranslateView(const Vector3& translation);
	void DeleteVAOHandle(GLuint m_vaoID);
	//CONSTANTS//////////////////////////////////////////////////////////////////////////
    static const int CIRCLE_SIDES = 50;
    static const int HEXAGON_SIDES = 6;
    static const unsigned char plainWhiteTexel[3];

    //MEMBER VARIABLES//////////////////////////////////////////////////////////////////////////
    static Renderer* instance;
    BitmapFont* m_defaultFont;
    Texture* m_defaultTexture;
    ShaderProgram* m_defaultShader;
    Material* m_defaultMaterial;
    Framebuffer* m_fbo;
    MatrixStack4x4 m_projStack;
    MatrixStack4x4 m_viewStack;
};