/**
* @file Vertex.h
* @brief 頂点情報を保存できる構造体の宣言
*/
#ifndef VERTEX_H_
#define VERTEX_H_

/////////////////////////////////
//!  カスタムバーテックス構造体
/////////////////////////////////
struct CUSTOMVERTEX{
    
    float x,y,z,rhw; //! x,y,zの座標、rhwは除算数

    unsigned long color; //! 色情報

    float tu,tv; //! テクスチャのUV座標
};

#endif //VERTEX_H_