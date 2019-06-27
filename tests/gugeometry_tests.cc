//
//  GUGeometryTests.cpp
//  gugridparticlefilter
//
//  Created by Callum McColl on 29/5/18.
//  Copyright © 2018 Vlad Estivill-Castro. All rights reserved.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma clang diagnostic ignored "-Wfloat-equal"

#include <gtest/gtest.h>
#include <guunits/CartesianEdge.h>
#include <guunits/CartesianCoordinate.h>
#include "../gugeometry.h"
#include <math.h>

#include <gu_util.h>

namespace CGTEST {
    
    class GUGeometryTests: public ::testing::Test {
    protected:
        
        virtual void SetUp() {
        }
        
        virtual void TearDown() {
        }

    };
        
    TEST_F(GUGeometryTests, CalculatesCorrectDistanceWhenBesideEdge) {
        const struct CartesianCoordinate e1 = CartesianCoordinate(0, 0);
        const struct CartesianCoordinate e2 = CartesianCoordinate(10, 0);
        const struct CartesianCoordinate p = CartesianCoordinate(-5, 0);
        ASSERT_EQ(distance_from_cartesian_edge(CartesianEdge(e1, e2), p), 5);
    }
    
    TEST_F(GUGeometryTests, CalculatesCorrectDistanceWhenAboveEdge) {
        const struct CartesianCoordinate e1 = CartesianCoordinate(0, 0);
        const struct CartesianCoordinate e2 = CartesianCoordinate(10, 0);
        const struct CartesianCoordinate p = CartesianCoordinate(5, 5);
        ASSERT_EQ(distance_from_cartesian_edge(CartesianEdge(e1, e2), p), 5);
    }
    
    TEST_F(GUGeometryTests, CalculatesCorrectDistanceWhenAboveEdgePoint) {
        const struct CartesianCoordinate e1 = CartesianCoordinate(0, 0);
        const struct CartesianCoordinate e2 = CartesianCoordinate(10, 0);
        const struct CartesianCoordinate p = CartesianCoordinate(10, 15);
        ASSERT_EQ(distance_from_cartesian_edge(CartesianEdge(e1, e2), p), 15);
    }
    
    TEST_F(GUGeometryTests, CalculatesCorrectDistanceForVerticleLineWhenBesideEdgePoint) {
        const struct CartesianCoordinate e1 = CartesianCoordinate(0, 0);
        const struct CartesianCoordinate e2 = CartesianCoordinate(0, 10);
        const struct CartesianCoordinate p = CartesianCoordinate(3, 10);
        ASSERT_EQ(distance_from_cartesian_edge(CartesianEdge(e1, e2), p), 3);
    }
    
    TEST_F(GUGeometryTests, CalculatesCorrectDistanceForVerticleLineWhenAboveEdgePoint) {
        const struct CartesianCoordinate e1 = CartesianCoordinate(0, 0);
        const struct CartesianCoordinate e2 = CartesianCoordinate(0, 10);
        const struct CartesianCoordinate p = CartesianCoordinate(0, 20);
        ASSERT_EQ(distance_from_cartesian_edge(CartesianEdge(e1, e2), p), 10);
    }
    
    TEST_F(GUGeometryTests, CalculatesCorrectDistanceForAboveAngledLine) {
        const struct CartesianCoordinate e1 = CartesianCoordinate(1, 1);
        const struct CartesianCoordinate e2 = CartesianCoordinate(2, 2);
        const struct CartesianCoordinate p = CartesianCoordinate(1, 3);
        ASSERT_EQ(int(distance_from_cartesian_edge(CartesianEdge(e1, e2), p) * 100000), int(sqrt(2) * 100000));
    }
    
    TEST_F(GUGeometryTests, CalculatesCorrectDistanceForBelowAngledLine) {
        const struct CartesianCoordinate e1 = CartesianCoordinate(1, 1);
        const struct CartesianCoordinate e2 = CartesianCoordinate(2, 2);
        const struct CartesianCoordinate p = CartesianCoordinate(3, 1);
        ASSERT_EQ(int(distance_from_cartesian_edge(CartesianEdge(e1, e2), p) * 100000), int(sqrt(2) * 100000));
    }
    
    TEST_F(GUGeometryTests, CalculatesCorrectDistanceForFarAwayPoint) {
        const struct CartesianCoordinate e1 = CartesianCoordinate(-200, -285);
        const struct CartesianCoordinate e2 = CartesianCoordinate(200, -285);
        const struct CartesianCoordinate p = CartesianCoordinate(-190, -275);
        ASSERT_EQ(int(distance_from_cartesian_edge(CartesianEdge(e1, e2), p)), 10);
    }

    TEST_F(GUGeometryTests, CalculatesCorrectAngleToEdge) {
        const Edge e = Edge(Coordinate(30, 10), Coordinate(-30, 15));
        ASSERT_EQ(rad_d_to_deg_t(angle_to_edge(e)), 17); 
    }

    TEST_F(GUGeometryTests, CalculatesCoorectAngleParallelToEdge) {
        const Edge e = Edge(Coordinate(28, 185), Coordinate(-33, 96));
        ASSERT_EQ(rad_d_to_deg_t(angle_parallel_to_edge(e)), 90);
    }


    TEST_F(GUGeometryTests, CalculatesCoorectAngleParallelToEdge2) {
        const Edge e = Edge(Coordinate(-8, 13), Coordinate(-9, 13));
        ASSERT_EQ(rad_d_to_deg_t(angle_parallel_to_edge(e)), 90);
    }

   
   /* 
    TEST_F(GUGeometryTests, CalculatesCorrectNormalisedAngleForPositiveAngle) {
        ASSERT_EQ(int(round(RAD2DEG(this->calculator->normaliseAngle(DEG2RAD(800.0f))))), 80);
    }
    
    TEST_F(GUGeometryTests, CalculatesCorrectNormalisedAngleForNegativeAngle) {
        ASSERT_EQ(int(round(RAD2DEG(this->calculator->normaliseAngle(DEG2RAD(-800.0f))))), 280);
    }*/
    
}  // namespace

#pragma clang diagnostic pop
