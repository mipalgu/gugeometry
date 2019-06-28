/*
 * gugeometry.h 
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

#ifndef GUGEOMETRY_H
#define GUGEOMETRY_H

#include <guunits/Coordinate.h>
#include <guunits/Edge.h>
#include <guunits/CartesianCoordinate.h>
#include <guunits/CartesianEdge.h>

#include "CircleOctant.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
bool between_edge(Edge edge, Coordinate coordinate);
*/

radians_d angle_between_points(struct cartesian_coordinate p1, struct cartesian_coordinate p2);
radians_d angle_for_octant(enum CircleOctant octant);
radians_d angle_from_octant(radians_d radians);
radians_d angle_of_cartesian_edge(struct cartesian_edge edge);
radians_d angle_of_edge(struct edge);
radians_d angle_parallel_to_edge(struct edge edge);
radians_d angle_to_edge(struct edge edge);
bool between_cartesian_edge(struct cartesian_edge edge, struct cartesian_coordinate point);
struct cartesian_coordinate coord_to_cart(struct coordinate coordinate);
struct cartesian_edge edge_to_cart(struct edge edge);
centimetres_d distance_between_points(struct cartesian_coordinate point1, struct cartesian_coordinate point2);
centimetres_d distance_from_cartesian_edge(struct cartesian_edge edge, struct cartesian_coordinate point);
centimetres_d distance_from_edge(struct edge edge);
enum CircleOctant octant(radians_d radians);

#ifdef __cplusplus
};
#endif

#endif  /* GUGEOMETRY_H */
