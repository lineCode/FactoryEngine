//
//  TestTetrahedron.m
//  FactoryEngine
//
//  Created by Edvinas Sarkus on 27/12/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <Model/PointNode.h>
#import <Model/Edge.h>
#import <Processing/FaceTraversal.h>

using namespace ftr;

@interface TestTetrahedron : XCTestCase
{
    PointNode* v1;
    PointNode* v2;
    PointNode* v3;
    PointNode* l4;
    PointNode* h4;
//    FaceTraversal traversal;
}

@end

@implementation TestTetrahedron

- (void)setUp
{
    [super setUp];
    v1 = new PointNode(glm::vec3(0.0f, 0.0f, -0.7f));
    v2 = new PointNode(glm::vec3(0.5f, 0.0f, 0.3f));
    v3 = new PointNode(glm::vec3(-0.5f, 0.0f, 0.3f));
    l4 = new PointNode(glm::vec3(0.0f, 0.3f, 0.0f)); // low
    h4 = new PointNode(glm::vec3(0.0f, 3.0f, 0.0f)); // high
    
    v1->mName = "1";
    v2->mName = "2";
    v3->mName = "3";
    l4->mName = "4";
    h4->mName = "4";
    
}

- (void)tearDown
{
    delete v1;
    delete v2;
    delete v3;
    delete l4;
    delete h4;
    [super tearDown];
}

- (void)testConnectingLowTetrahedron
{
    PointNode::ConnectionResult e12 = v1->ConnectTo(v2);
    PointNode::ConnectionResult e23 = v2->ConnectTo(v3);
    PointNode::ConnectionResult e31 = v3->ConnectTo(v1);
    
    PointNode::ConnectionResult e14 = v1->ConnectTo(l4);
    PointNode::ConnectionResult e24 = v2->ConnectTo(l4);
    PointNode::ConnectionResult e34 = v3->ConnectTo(l4);
    
    XCTAssert(e31.faceA || e31.faceB);
    XCTAssert(e24.faceA || e24.faceB);
    XCTAssert(e34.faceA && e34.faceB);
}

- (void)testConnectingHighTetrahedron
{
    
}

@end