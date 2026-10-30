//
// Created by Ishaan Sayal.
// Copyright (c) 2026 Stevens Electric Boatworks.

#pragma once
#include <cstdint>
#include <string>

namespace eboat {
    class FrameWriter {
    public:
        explicit FrameWriter(const uint8_t header) {
            buf_.reserve(8);
            u8(header);
        }

        FrameWriter& u8(uint8_t v) {
            buf_.push_back(static_cast<char>(v));
            return *this;
        }

        FrameWriter& u16(const uint16_t v) {
            u8(static_cast<uint8_t>(v));
            u8(static_cast<uint8_t>(v >> 8));
            return *this;
        }

        FrameWriter& u32(uint32_t v) {
            u16(static_cast<uint16_t>(v));
            u16(static_cast<uint16_t>(v >> 16));
            return *this;
        }

        FrameWriter& i8(const int8_t v)   { return u8(static_cast<uint8_t>(v)); }
        FrameWriter& i16(const int16_t v) { return u16(static_cast<uint16_t>(v)); }
        FrameWriter& i32(const int32_t v) { return u32(static_cast<uint32_t>(v)); }

        std::string finish(const uint8_t pad = 0x00) {
            while (buf_.size() < 8) u8(pad);
            return std::move(buf_);
        }

    private:
        std::string buf_;
    };
}
