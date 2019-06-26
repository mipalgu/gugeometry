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
#include <stdint.h>
#include <math.h>

/*
bool between_cartesian_edge(CartesianEdge edge, CartesianCoordinate point)
{
    // Horizontal Lines
    if (edge.leftPoint.x == edge.rightPoint.x) {
        const CartesianCoordinate re1 = edge.leftPoint.y < edge.rightPoint.y ? edge.leftPoint() : edge.rightPoint();
        const CartesianCoordinate re2 = edge.leftPoint.y < edge.rightPoint.y ? edge.rightPoint() : edge.leftPoint();
        return point.y >= re1.y && point.y <= re2.y;
    }
    // Veritcal Lines
    if (edge.leftPoint.y == edge.rightPoint.y) {
        const CartesianCoordinate re1 = edge.leftPoint.x < edge.rightPoint.x ? edge.leftPoint() : edge.rightPoint();
        const CartesianCoordinate re2 = edge.leftPoint.x < edge.rightPoint.x ? edge.rightPoint() : edge.leftPoint();
        return point.x >= re1.x && point.x <= re2.x;
    }
    // All other lines.
    const CartesianCoordinate leftEdge = edge.leftPoint.x < edge.rightPoint.x ? edge.leftPoint() : edge.rightPoint();
    const CartesianCoordinate rightEdge = edge.leftPoint.x < edge.rightPoint.x ? edge.rightPoint() : edge.leftPoint();
    const CartesianCoordinate midPoint = CartesianCoordinate(rightEdge.x - leftEdge.x, rightEdge.y - leftEdge.y);
    // Translate by edge so that it goes through the origin.
    const CartesianCoordinate t1 = CartesianCoordinate(leftEdge.x - midPoint.x, leftEdge.y - midPoint.y);
    const CartesianCoordinate t2 = CartesianCoordinate(rightEdge.x - midPoint.x, rightEdge.y - midPoint.y);
    const CartesianCoordinate tpoint = CartesianCoordinate(point.x - midPoint.x, point.y - midPoint.y);
    // Rotate the translated edge so that it is inline with the x axis.
    const float angle = rad_f_to_f(deg_f_to_rad_f(angle_between_points(CartesianCoordinate(0, 0), t2)));
    const CartesianCoordinate r1 = CartesianCoordinate((int) (round(((float) (t1.x)) * cos(angle))), (int) (round(((float) (t1.y)) * sin(angle))));
    const CartesianCoordinate r2 = CartesianCoordinate((int) (round(((float) (t2.x)) * cos(angle))), (int) (round(((float) (t2.y)) * sin(angle))));
    const CartesianCoordinate rpoint = CartesianCoordinate((int) (round(((float) (tpoint.x)) * cos(angle))), (int) (round(((float) (tpoint.y)) * sin(angle))));
    // Check the x values to see if the point is between the points of the edge.
    return rpoint.x >= r1.x && rpoint.x <= r2.x;
}


CartesianCoordinate to_cartesian(Coordinate coordinate)
{
    const float radius = cm_u_to_f(coordinate.distance());
    const float theta = rad_f_to_f(deg_t_to_rad_f(coordinate.direction()));
    const int x = int(round(radius * cos(theta)));
    const int y = int(round(radius * sin(theta)));
    return CartesianCoordinate(x, y);
}

degrees_f angle_between_points(CartesianCoordinate p1, CartesianCoordinate p2)
{
    const int dx = p2.x - p1.x;
    const int dy = p2.y - p1.y;
    if (0 == dx) {
        if (0 == dy) {
            return 0.0f;
        }
        return dy > 0 ? f_to_deg_f(90.0f) : f_to_deg_f(-90.0f);
    }
    return rad_f_to_deg_f(f_to_rad_f(atan2((float) (dy), (float) (dx))));
}
*/

CircleOctant octant(degrees_t degrees)
{
    const float angle = rad_f_to_f(deg_t_to_rad_f(degrees));
    if (angle < 0) {
        return this->octant(angle + float(2 * M_PI));
    }
    if (angle < M_PI / 4.0f) {
        return FirstOctant;
    }
    if (angle < M_PI / 2.0f) {
        return SecondOctant;
    }
    if (angle < 3 * M_PI / 4.0f) {
        return ThirdOctant;
    }
    if (angle < M_PI) {
        return FourthOctant;
    }
    if (angle < M_PI * 5 / 4.0f) {
        return FifthOctant;
    }
    if (angle < M_PI * 3 / 2.0f) {
        return SixthOctant;
    }
    if (angle < M_PI * 7 / 4.0f) {
        return SeventhOctant;
    }
    if (angle < M_PI * 2) {
        return EightOctant;
    }
    return octant(angle - float(2 * M_PI));
}
