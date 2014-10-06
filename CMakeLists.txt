# This file is part of typoratio.
#
# typoratio is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# typoratio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with typoratio. If not, see <http://www.gnu.org/licenses/>.
#
# Copyright 2014 Chris Foster

cmake_minimum_required(VERSION 2.8)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message(FATAL_ERROR "In-source builds are not allowed!")
endif()

project(typoratio)

add_executable(typoratio typoratio.c)

target_link_libraries(typoratio m)
