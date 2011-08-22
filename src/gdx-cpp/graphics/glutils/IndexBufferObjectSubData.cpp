
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#include "IndexBufferObjectSubData.hpp"

using namespace gdx_cpp::graphics::glutils;

int IndexBufferObjectSubData::createBufferObject () {
    if (Gdx.gl20 != null) {
        Gdx.gl20.glGenBuffers(1, tmpHandle);
        Gdx.gl20.glBindBuffer(GL20.GL_ELEMENT_ARRAY_BUFFER, tmpHandle.get(0));
        Gdx.gl20.glBufferData(GL20.GL_ELEMENT_ARRAY_BUFFER, byteBuffer.capacity(), null, usage);
        Gdx.gl20.glBindBuffer(GL20.GL_ELEMENT_ARRAY_BUFFER, 0);
        return tmpHandle.get(0);
    } else if (Gdx.gl11 != null) {
        Gdx.gl11.glGenBuffers(1, tmpHandle);
        Gdx.gl11.glBindBuffer(GL11.GL_ELEMENT_ARRAY_BUFFER, tmpHandle.get(0));
        Gdx.gl11.glBufferData(GL11.GL_ELEMENT_ARRAY_BUFFER, byteBuffer.capacity(), null, usage);
        Gdx.gl11.glBindBuffer(GL11.GL_ELEMENT_ARRAY_BUFFER, 0);
        return tmpHandle.get(0);
    }

    return 0;
}

int IndexBufferObjectSubData::getNumIndices () {
    return buffer.limit();
}

int IndexBufferObjectSubData::getNumMaxIndices () {
    return buffer.capacity();
}

void IndexBufferObjectSubData::setIndices (int offset,int count) {
    isDirty = true;
    buffer.clear();
    buffer.put(indices, offset, count);
    buffer.flip();
    byteBuffer.position(0);
    byteBuffer.limit(count << 1);

    if (isBound) {
        if (Gdx.gl11 != null) {
            GL11 gl = Gdx.gl11;
// gl.glBufferData(GL11.GL_ELEMENT_ARRAY_BUFFER, byteBuffer
// .limit(), byteBuffer, usage);
            gl.glBufferSubData(GL11.GL_ELEMENT_ARRAY_BUFFER, 0, byteBuffer.limit(), byteBuffer);
        } else if (Gdx.gl11 != null) {
            GL20 gl = Gdx.gl20;
// gl.glBufferData(GL20.GL_ELEMENT_ARRAY_BUFFER, byteBuffer
// .limit(), byteBuffer, usage);
            gl.glBufferSubData(GL20.GL_ELEMENT_ARRAY_BUFFER, 0, byteBuffer.limit(), byteBuffer);

        }
        isDirty = false;
    }
}

ShortBuffer& IndexBufferObjectSubData::getBuffer () {
    isDirty = true;
    return buffer;
}

void IndexBufferObjectSubData::bind () {
    if (bufferHandle == 0) throw new GdxRuntimeException("buuh");

    if (Gdx.gl11 != null) {
        GL11 gl = Gdx.gl11;
        gl.glBindBuffer(GL11.GL_ELEMENT_ARRAY_BUFFER, bufferHandle);
        if (isDirty) {
// gl.glBufferData(GL11.GL_ELEMENT_ARRAY_BUFFER, byteBuffer
// .limit(), byteBuffer, usage);
            byteBuffer.limit(buffer.limit() * 2);
            gl.glBufferSubData(GL11.GL_ELEMENT_ARRAY_BUFFER, 0, byteBuffer.limit(), byteBuffer);
            isDirty = false;
        }
    } else {
        GL20 gl = Gdx.gl20;
        gl.glBindBuffer(GL20.GL_ELEMENT_ARRAY_BUFFER, bufferHandle);
        if (isDirty) {
// gl.glBufferData(GL20.GL_ELEMENT_ARRAY_BUFFER, byteBuffer
// .limit(), byteBuffer, usage);
            byteBuffer.limit(buffer.limit() * 2);
            gl.glBufferSubData(GL20.GL_ELEMENT_ARRAY_BUFFER, 0, byteBuffer.limit(), byteBuffer);
            isDirty = false;
        }
    }
    isBound = true;
}

void IndexBufferObjectSubData::unbind () {
    if (Gdx.gl11 != null) {
        Gdx.gl11.glBindBuffer(GL11.GL_ELEMENT_ARRAY_BUFFER, 0);
    } else if (Gdx.gl20 != null) {
        Gdx.gl20.glBindBuffer(GL11.GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    isBound = false;
}

void IndexBufferObjectSubData::invalidate () {
    bufferHandle = createBufferObject();
    isDirty = true;
}

void IndexBufferObjectSubData::dispose () {
    if (Gdx.gl20 != null) {
        tmpHandle.clear();
        tmpHandle.put(bufferHandle);
        tmpHandle.flip();
        GL20 gl = Gdx.gl20;
        gl.glBindBuffer(GL20.GL_ELEMENT_ARRAY_BUFFER, 0);
        gl.glDeleteBuffers(1, tmpHandle);
        bufferHandle = 0;
    } else if (Gdx.gl11 != null) {
        tmpHandle.clear();
        tmpHandle.put(bufferHandle);
        tmpHandle.flip();
        GL11 gl = Gdx.gl11;
        gl.glBindBuffer(GL11.GL_ELEMENT_ARRAY_BUFFER, 0);
        gl.glDeleteBuffers(1, tmpHandle);
        bufferHandle = 0;
    }
}
