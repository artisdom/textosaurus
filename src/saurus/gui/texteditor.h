// For license of this file, see <project-root-folder>/LICENSE.md.

#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "3rd-party/scintilla/qt/ScintillaEdit/ScintillaEdit.h"

#include "definitions/definitions.h"
#include "saurus/miscellaneous/syntaxhighlighting.h"

#include <QFile>
#include <QMessageBox>

#define QCOLOR_TO_SPRT(col) ((col.blue()) << 16) | ((col.green()) << 8) | (col.red())
#define RGB_TO_SPRT(b, g, r) ((r) << 16) | ((g) << 8) | (b)

class TextApplication;
class QFileSystemWatcher;

struct FileInitialMetadata {
  QString m_encoding;
  Lexer m_lexer;
  int m_eolMode;
};

class TextEditor : public ScintillaEdit {
  Q_OBJECT

  public:
    explicit TextEditor(TextApplication* text_app, QWidget* parent = nullptr);
    virtual ~TextEditor() = default;

    QString filePath() const;
    Lexer lexer() const;

    QByteArray encoding() const;
    void setEncoding(const QByteArray& encoding);

    bool settingsDirty() const;
    void setSettingsDirty(bool settings_dirty);

    void setReadOnly(bool read_only);

    static TextEditor* fromTextFile(TextApplication* app, const QString& file_path, const QString& explicit_encoding = QString());
    static FileInitialMetadata getInitialMetadata(const QString& file_path, const QString& explicit_encoding = QString());

    bool isLog() const;
    void setIsLog(bool is_log);

    bool autoIndentEnabled() const;
    void setAutoIndentEnabled(bool auto_indent_enabled);
    void setFilePath(const QString& file_path);

    QMessageBox::StandardButton currentSaveAgreement() const;

  public slots:
    void resetSaveAgreement();
    void askForSaveAgreement();

    void reloadFromDisk();
    void toggleFolding(int position, int modifiers, int margin);
    void printPreview();
    void print();
    void save(bool* ok);
    void saveAs(bool* ok, const QString& encoding = QString());

    // Shows/hides line numbers margin and adjusts its size to
    // current line count and zoom.
    void updateLineNumberMarginVisibility();
    void reloadFont();
    void reloadSettings();
    void reloadLexer(const Lexer& default_lexer);

    // Closes the editor, user is asked to save unsaved text document.
    // Given parameter is used to indicate if closing was finished (true)
    // or user cancelled it (false).
    void closeEditor(bool* ok);
    void loadFromFile(QFile& file, const QString& encoding, const Lexer& default_lexer, int initial_eol_mode);
    void loadFromString(const QString& contents);

  private slots:
    void findAllFromSelectedText();
    void updateUrlHighlights();
    void updateOccurrencesHighlights();
    void uiUpdated(int code);
    void onCharAdded(int chr);
    void onNotification(SCNotification* pscn);
    void onFileExternallyChanged(const QString& file_path);
    void onModified(int type, int position, int length, int lines_added, const QByteArray& text,
                    int line, int fold_now, int fold_prev);

  protected:
    virtual void contextMenuEvent(QContextMenuEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;

  signals:
    void readOnlyChanged(bool read_only);
    void editorReloaded();
    void requestedVisibility();
    void loadedFromFile(QString source_file_path);
    void savedToFile(QString destination_file_path);

  private:
    void appendSessionFile(const QString& file_name, bool is_nonexistent);

    void detachWatcher();
    void reattachWatcher(const QString& file_path);
    bool isMarginVisible(int margin_number) const;
    void updateLineNumberMarginWidth(sptr_t zoom, QFont font, sptr_t line_count);
    void saveToFile(const QString& file_path, bool* ok, const QString& encoding = QString());

    // Returns filename relative to "user data" folder.
    // NOTE: This is used for saving of unattached editors
    // to session files.
    QString getSessionFile();

  private:
    QMessageBox::StandardButton m_saveAgreement;
    bool m_isLog;
    QFileSystemWatcher* m_fileWatcher;
    bool m_settingsDirty;
    TextApplication* m_textApp;
    QString m_filePath;
    QByteArray m_encoding;
    Lexer m_lexer;
    bool m_autoIndentEnabled;
};

#endif // TEXTEDITOR_H
