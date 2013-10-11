#include "meshParticle.h"

meshParticle::meshParticle() {
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
}

meshParticle::~meshParticle(){}

void meshParticle::update(float dt) {

//    this->BaseParticle::update(dt);
//    timer += dt;
//    if (timer >= temporalResolution) {
//        timer = 0.0;
//
//        // Get the vertices
//        ofVec3f t = center+rotatedTop;
//        ofVec3f l = center+rotatedLeft;
//        ofVec3f r = center+rotatedRight;
//        ofVec3f lt = lastTop;
//        ofVec3f ll = lastLeft;
//        ofVec3f lr = lastRight;
//
//        // Add the newest vertices
//        mesh.addVertex(t);
////            mesh.addColor(ofFloatColor(255,0,0));
//        mesh.addIndex(i);
//
//        mesh.addVertex(l);
////            mesh.addColor(ofFloatColor(0,255,0));
//        mesh.addIndex(i+1);
//
//        mesh.addVertex(r);
////            mesh.addColor(ofFloatColor(0,0,255));
//        mesh.addIndex(i+2);
//        i+=3;
//
//        // Get the indicies
//        int lti = i-6;
//        int lli = i-5;
//        int lri = i-4;
//        int ti = i-3;
//        int li = i-2;
//        int ri = i-1;
//
//        // Create a face for the new verts
//        mesh.addTriangle(ti, li, ri);
//
//        // If there was a prior face, connect it to the new one
//        if (i >= 6){
//            mesh.addTriangle(lti, ti, lri);
//            mesh.addTriangle(lri, ti, ri);
//            mesh.addTriangle(lti, ti, lli);
//            mesh.addTriangle(lli, ti, li);
//            mesh.addTriangle(lli, ri, lri);
//            mesh.addTriangle(lli, li, ri);
//        }
//
//        // Store the newest verts
//        lastTop = t;
//        lastLeft = l;
//        lastRight = r;
//    }
}


void meshParticle::draw() {
//    this->BaseParticle::draw();

    mesh.draw();

}
