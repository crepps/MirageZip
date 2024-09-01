/*****************************************************************//**
 * @file   miragezip.h
 * @brief  This file defines the interface for the MirageZip
 *         back end, and provides functions for setting a password
 *         and evaluating its strength, zipping and encrypting
 *         imported files with libzip, and concatenating the
 *         archive with an imported image file.
 *
 * @author Kevin Crepps
 * @date   August 2024
 *********************************************************************/

#pragma once

#include <sstream>
#include <fstream>
#include <filesystem>
#include <memory>

#include <Windows.h>

#include "zip.h"

 /**
  * Custom return codes specifying that
  * a given operation:
  *
  * - Succeeded (0)
  * - Failed and aborting is recommended (1)
  * - Failed but program can safely continue (2)
  */
#define SUCCESS 0
#define FAILURE_ABORT 1
#define FAILURE_CONTINUE 2

  /**
   * Constants used in determining password strength.
   */
#define WEAK_SCORE 2
#define MEDIUM_SCORE 3
#define STRONG_SCORE 4
#define MEDIUM_LENGTH 8
#define STRONG_LENGTH 12
#define NUM_SETS 4


class MirageZip
{
public:
    /**
     * Used to specify path type with SetPath().
     */
    enum PATH_TYPE
    {
        IMAGE,
        FILE,
        EXPORT
    };

    /**
     * @brief
     * Password containing null terminator is indicative of initial
     * state. Call private function Init() to create app data folder.
     */
    MirageZip() : password("\0") { Init(); }

    /**
    * @brief
    * Stores error description for later retrieval using GetError().
    *
    * Overloaded for rvalues.
    */
    inline void SetError(std::string&& arg) noexcept { error = std::move(arg); }

    /**
     * @brief
     * Stores error description for later retrieval using GetError().
     *
     * Overloaded for lvalues.
     */
    inline void SetError(const std::string& arg) noexcept { error = std::move(arg); }

    /**
     * @brief
     * Retrieve exception info and other error messages set
     * internally with SetError().
     */
    inline std::string GetError() const noexcept { return error; }

    /**
     * @brief
     * User sets the path of an image, file(s), and export location,
     * specified with PATH_TYPE enum defined above.
     */
    void SetPath(PATH_TYPE, const std::string&) noexcept;

    /**
     * @brief
     * Use point system to evaluate password strength based on
     * character diversity and length.
     *
     * @return
     * Returns password strength score indicating:
     *   weak - fewer than three points
     *   medium - three points
     *   strong - four points
     */
    unsigned int TestPassword(const std::string&) const noexcept;

    /**
     * @brief
     * Set the password after evaluating, used to encrypt file
     * archive in ZipFile().
     */
    inline void SetPassword(const std::string& arg) noexcept { password = arg; }

    /**
     * @brief
     * Zip and password-protect files using libzip functions.
     *
     * @return
     * Custom return code defined at the top of miragezip.h.
     */
    unsigned int ZipFile();

    /**
     * @brief
     * Combines image and archive using Windows copy command
     * with binary flag, issued through CreateProcessA().
     */
    unsigned int Concatenate() const;

    /**
    * @brief
    * Get path of new zip file - used in HideFile().
    */
    inline const char* GetArchivePath() const noexcept { return archivePath.c_str(); }

    ~MirageZip() {}

private:
    std::string error,      // Error info buffer, set in SetError()
        archivePath,        // Path to zip; this is set in CreateAppData()
        imagePath,          // Path to user-selected image file
        filePath,           // Path to user-selected file to be zipped
        exportPath,         // Destination of output file
        password;           // Password used to encrypt archive

    struct stat Statinfo;   /* Used for checking whether
                                directory exists with stat() */

                                /**
                                 * Character set types used in password evaluation.
                                 */
    enum CHAR_TYPE
    {
        LOWER,
        UPPER,
        NUMBERS,
        CHARACTERS
    };

    /**
     * @brief
     * Called from the constructor. CreateAppData is run from here.
     * If unable to create directory, user is notified, program terminates.
     */
    void Init();

    /**
     * @brief
     * Checks for existance of %LOCALAPPDATA%\MirageZip, attempts to
     * create it if it doesn't exist.
     *
     * @return
     * Custom return code defined at the top of miragezip.h.
     */
    unsigned int CreateAppData();
};

/**
 * @brief
 * Non-member non-friend function attempts to zip file,
 * combine it with image, then purge app data files.
 */
extern unsigned int HideFile(MirageZip* obj);