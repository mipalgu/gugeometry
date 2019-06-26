/*
 * gugeometry.cc 
 * gugeometry 
 *
 * Created by Callum McColl on 26/06/2019.
 * Copyright © 2019 Callum McColl. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgement:
 *
 *        This product includes software developed by Callum McColl.
 *
 * 4. Neither the name of the author nor the names of contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * -----------------------------------------------------------------------
 * This program is free software; you can redistribute it and/or
 * modify it under the above terms or under the terms of the GNU
 * General Public License as published by the Free Software Foundation;
 * either version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see http://www.gnu.org/licenses/
 * or write to the Free Software Foundation, Inc., 51 Franklin Street,
 * Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include "gugeometry.h"

#include <guunits/guunits.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

radians_d angle_between_points(struct CartesianCoordinate p1, struct CartesianCoordinate p2)
{
    const int dx = p2.x - p1.x;
    const int dy = p2.y - p1.y;
    if (0 == dx) {
        if (0 == dy) {
            return 0.0;
        }
        return dy > 0 ? d_to_rad_d(90.0) : d_to_rad_d(-90.0);
    }
    return d_to_rad_d(atan2((double) (dy), (double) (dx)));
}

radians_d angle_for_octant(enum CircleOctant octant)
{
    switch (octant) {
    case FirstOctant:
        return 0.0;
    case SecondOctant:
        return deg_d_to_rad_d(45.0);
    case ThirdOctant:
        return deg_d_to_rad_d(90.0);
    case FourthOctant:
        return deg_d_to_rad_d(135.0);
    case FifthOctant:
        return deg_d_to_rad_d(180.0);
    case SixthOctant:
        return deg_d_to_rad_d(225.0);
    case SeventhOctant:
        return deg_d_to_rad_d(270.0);
    case EightOctant:
        return deg_d_to_rad_d(315.0);
    }
}

radians_d angle_from_octant(radians_d radians)
{
    const double angle = rad_d_to_d(radians);
    const enum CircleOctant oct = octant(radians);
    const double octantAngle = rad_d_to_d(angle_for_octant(oct)) + (oct % 2 == 0 ? 0.0 : rad_d_to_d(deg_d_to_rad_d(45.0)));
    if (oct % 2 == 0) {
        return d_to_rad_d(angle - octantAngle);
    }
    return d_to_rad_d(octantAngle - angle);
}

bool between_cartesian_edge(struct CartesianEdge edge, struct CartesianCoordinate point)
{
    // Horizontal Lines
    if (edge.leftPoint.x == edge.rightPoint.x) {
        const struct CartesianCoordinate re1 = edge.leftPoint.y < edge.rightPoint.y ? edge.leftPoint : edge.rightPoint;
        const struct CartesianCoordinate re2 = edge.leftPoint.y < edge.rightPoint.y ? edge.rightPoint : edge.leftPoint;
        return point.y >= re1.y && point.y <= re2.y;
    }
    // Veritcal Lines
    if (edge.leftPoint.y == edge.rightPoint.y) {
        const struct CartesianCoordinate re1 = edge.leftPoint.x < edge.rightPoint.x ? edge.leftPoint : edge.rightPoint;
        const struct CartesianCoordinate re2 = edge.leftPoint.x < edge.rightPoint.x ? edge.rightPoint : edge.leftPoint;
        return point.x >= re1.x && point.x <= re2.x;
    }
    // All other lines.
    const struct CartesianCoordinate leftEdge = edge.leftPoint.x < edge.rightPoint.x ? edge.leftPoint : edge.rightPoint;
    const struct CartesianCoordinate rightEdge = edge.leftPoint.x < edge.rightPoint.x ? edge.rightPoint : edge.leftPoint;
    const struct CartesianCoordinate midPoint = { rightEdge.x - leftEdge.x, rightEdge.y - leftEdge.y };
    // Translate by edge so that it goes through the origin.
    const struct CartesianCoordinate t1 = { leftEdge.x - midPoint.x, leftEdge.y - midPoint.y };
    const struct CartesianCoordinate t2 = { rightEdge.x - midPoint.x, rightEdge.y - midPoint.y };
    const struct CartesianCoordinate tpoint = { point.x - midPoint.x, point.y - midPoint.y };
    // Rotate the translated edge so that it is inline with the x axis.
    const struct CartesianCoordinate origin = {0, 0};
    const double angle = rad_d_to_d(deg_d_to_rad_d(angle_between_points(origin, t2)));
    const struct CartesianCoordinate r1 = { (int) (round(((double) (t1.x)) * cos(angle))), (int) (round(((double) (t1.y)) * sin(angle))) };
    const struct CartesianCoordinate r2 = { (int) (round(((double) (t2.x)) * cos(angle))), (int) (round(((double) (t2.y)) * sin(angle))) };
    const struct CartesianCoordinate rpoint = { (int) (round(((double) (tpoint.x)) * cos(angle))), (int) (round(((double) (tpoint.y)) * sin(angle))) };
    // Check the x values to see if the point is between the points of the edge.
    return rpoint.x >= r1.x && rpoint.x <= r2.x;
}

struct CartesianCoordinate coord_to_cart(struct Coordinate coordinate)
{
    const double radius = cm_u_to_d(coordinate.distance);
    const double theta = rad_d_to_d(deg_t_to_rad_d(coordinate.direction));
    const int x = (int) (round(radius * cos(theta)));
    const int y = (int) (round(radius * sin(theta)));
    const struct CartesianCoordinate result = {x, y};
    return result;
}

double distance_between_points(struct CartesianCoordinate point1, struct CartesianCoordinate point2)
{
    const struct CartesianCoordinate dpoint = { point2.x - point1.x, point2.y - point1.y };
    // Horizontal Lines
    if (0 == dpoint.x) {
        return ((double) (abs(dpoint.y)));
    }
    // Veritcal Lines
    if (0 == dpoint.y) {
        return ((double) (abs(dpoint.x)));
    }
    return sqrt(((double) (dpoint.x * dpoint.x)) + ((double) (dpoint.y * dpoint.y)));
}

double distance_from_cartesian_edge(struct CartesianEdge edge, struct CartesianCoordinate point)
{
   // If we are not within the bounds of the edge then calculate the distance from the nearest edge point.
    if (!between_cartesian_edge(edge, point))
    {
        return MIN(distance_between_points(edge.leftPoint, point), distance_between_points(edge.rightPoint, point));
    }
    // Calculate the distance from the line to the point.
    const double x0 = (double) (point.x);
    const double y0 = (double) (point.y);
    const double x1 = (double) (edge.leftPoint.x);
    const double y1 = (double) (edge.leftPoint.y);
    const double x2 = (double) (edge.rightPoint.x);
    const double y2 = (double) (edge.rightPoint.y);
    return fabs((y2 - y1) * x0 - (x2 - x1) * y0 + x2 * y1 - y2 * x1) / sqrt(((y2 - y1) * (y2 - y1)) + ((x2 - x1) * (x2 - x1))); 
}

enum CircleOctant octant(radians_d radians)
{
    const double angle = rad_d_to_d(radians);
    if (angle < 0) {
        return octant(d_to_rad_d(angle + (2.0 * M_PI)));
    }
    if (angle < M_PI / 4.0) {
        return FirstOctant;
    }
    if (angle < M_PI / 2.0) {
        return SecondOctant;
    }
    if (angle < 3 * M_PI / 4.0) {
        return ThirdOctant;
    }
    if (angle < M_PI) {
        return FourthOctant;
    }
    if (angle < M_PI * 5 / 4.0) {
        return FifthOctant;
    }
    if (angle < M_PI * 3 / 2.0) {
        return SixthOctant;
    }
    if (angle < M_PI * 7 / 4.0) {
        return SeventhOctant;
    }
    if (angle < M_PI * 2) {
        return EightOctant;
    }
    return octant(d_to_rad_d(angle - (2.0 * M_PI)));
}
