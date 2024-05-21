# MirageZip

A utility for hiding files inside of images to provide security through obscurity, as well as password protection using 256-bit AES encryption. This is done by simply appending your files' (compressed) data to that of the selected image's binary data.

1. Select the image in which you would like to hide your file (.jpg, .jpeg, .png, .bmp, .gif or .pdf).

2. Select any kind of file to hide.

3. Choose the name and location of a new image that will contain your data (use the same file extension as the imported image).

4. Enter a password (if discovered, the security of your data will depend on the complexity of your password).

5. Right click the new image -> 'Open with' -> 'Choose another app' -> Select the file archiver of your choice (WinZip, WinRar, etc).

The new image will open and behave the same as the original, but with an increased file size. Drop it in with other images to obscure the whereabouts of your sensitive data, or use it for an added layer of security when transferring data to others, or between systems.

This utility uses the libzip library for compression and encryption (https://libzip.org).
