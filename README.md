# Simple Media


Media formats often provide impressive compression, but at the cost of absurd complexity. This is the opposite approach: a set of media formats designed to be very simple while providing "good enough" compression.

File formats include:
* image (.simg)
* audio (.saud)
* video (.svid)
* streamable video (.strm)


This project is currently in an exploratory mode. Nothing is finalized yet, and formats may change substantially.

Current plan:
* Use simple encoding strategies like RLE, difference encodings, etc.
* Compress blocks of encodings with secondary compression: bit packing, bit tables, etc.
* Provide some support for lossy compression
