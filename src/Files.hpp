/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License")
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef GDX_CPP_FILES_H
#define GDX_CPP_FILES_H

#include <string>

namespace gdx_cpp {

/** Provides standard access to the filesystem, classpath, Android SD card, and Android assets directory.
 * @author mzechner
 * @author Nathan Sweet */
class Files {
    /** Indicates how to resolve a path to a file.
     * @author mzechner
     * @author Nathan Sweet */
    enum FileType {
        /** Path relative to the asset directory on Android and to the application's root directory on the desktop. On the desktop,
         * if the file is not found, then the classpath is checked. This enables files to be found when using JWS or applets.
         * Internal files are always readonly. */
        Internal,

        /** Path relative to the root of the SD card on Android and to the home directory of the current user on the desktop. */
        External,

        /** Path that is a fully qualified, absolute filesystem path. To ensure portability across platforms use absolute files only
         * when absolutely (heh) necessary. */
        Absolute
    };

    /** Returns a handle representing a file or directory.
     * @param type Determines how the path is resolved.
     * @throws GdxRuntimeException if the type is classpath or internal and the file does not exist.
     * @see FileType */
    virtual FileHandle getFileHandle (stlport::string& path, FileType type) = 0;

    /** Convenience method that returns a {@link FileType#Classpath} file handle. */
    virtual FileHandle classpath (stlport::string& path) = 0;

    /** Convenience method that returns a {@link FileType#Internal} file handle. */
    virtual FileHandle internal (stlport::string& path) = 0;

    /** Convenience method that returns a {@link FileType#External} file handle. */
    virtual FileHandle external (stlport::string& path) = 0;

    /** Convenience method that returns a {@link FileType#Absolute} file handle. */
    virtual FileHandle absolute (stlport::string& path) = 0;

    /** Returns the external storage path directory. This is the SD card on Android and the home directory of the current user on
     * the desktop. */
    virtual stlport::string& getExternalStoragePath () = 0;

    /** Returns true if the external storage is ready for file IO. Eg, on Android, the SD card is not available when mounted for use
     * with a PC. */
    virtual bool isExternalStorageAvailable () = 0;
};

}

#endif // GDX_CPP_FILES_H