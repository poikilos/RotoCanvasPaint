#ifndef ROTOCANVAS_H
#define ROTOCANVAS_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QList>
#include <QFileInfo>
#include <rotocanvaslayer.h>
//! [0]
class RotoCanvas : public QWidget
{
    Q_OBJECT

public:
    RotoCanvas(QWidget *parent = 0);

    static QString getSeqName(QString framePath);
    static QString getSeqName(QFileInfo frameFI);
    QString getSeqName();
    static QString getSeqFormatString(QString framePath);
    static QString getSeqFormatString(QFileInfo frameFI);
    QString getSeqFormatString();
    static QString getFolderPath(QString framePath);
    static QString getFolderPath(QFileInfo frameFI);
    QString getFolderPath();
    static int getSeqFrameNumber(QString framePath);
    static int getSeqFrameNumber(QFileInfo frameFI);
    int getSeqFrameNumber();
    static int getSeqDigitCount(QString framePath);
    static int getSeqDigitCount(QFileInfo frameFI);
    int getSeqDigitCount();
    static QString getSeqPaddedFrameNumber(QString framePath);
    static QString getSeqPaddedFrameNumber(QFileInfo frameFI);
    QString getSeqPaddedFrameNumber();
    static QString getLayersFolderPath(QString framePath, int frameNumber, bool createEnable);
    static QString getLayersFolderPath(QFileInfo frameFI, int frameNumber, bool createEnable);
    QString getLayersFolderPath(int frameNumber, bool createEnable);
    static QString getLayerImagePathMostRecent(QString framePath, int frameNumber, int layerNumber);
    static QString getLayerImagePathMostRecent(QFileInfo frameFI, int frameNumber, int layerNumber);
    QString getLayerImagePathMostRecent(int frameNumber, int layerNumber);

    static QString getSeqFramePath(QString folderPath, QString seqName, int frameNumber, int minDigitCount, QString format);
    QString getSeqFramePath(int frameNumber);
    static QString getZeroPadded(int frameNumber, int minDigitCount);


    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setBrushColor(const QColor &newColor);
    void setBrushRadius(double newWidth);
    void setBrushHardness(double newHardness);
    void setBrushOpacity(double newOpacity);

    bool getIsModified() const { return isModified; }
    QColor getBrushColor() const { return brushColor; }
    double getBrushRadius() const { return brushRadius; }
    double getBrushHardness() const { return (brushRadius-brushHardRadius)/brushRadius; }
    double getBrushOpacity() const { return brushOpacity; }

public slots:
    void clearImage();
    void print();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    void drawLineTo(const QPoint &endPoint);
    void fillCheckered(QImage *thisImage);
    void resizeImage(QImage *thisImage, const QSize &newSize);
    QImage getCacheableImage(QString filePath);

    bool isModified;
    bool isToolActive;
    int selectedLayerIndex;
    double cacheMaxMB;
    //int minDigitCount;  // use getSeqDigitCount; formerly PROJECT INFO
    double brushRadius; // PROJECT INFO
    double brushHardRadius; // PROJECT INFO
    double brushOpacity; // PROJECT INFO
    QFileInfo* loadedFI; // PROJECT INFO; STATE INFO: background layer
    QSize outputSize;  // PROJECT INFO size of video (same as layers, but different from image)
    QColor brushColor; // PROJECT INFO
    QColor checkerDarkColor; // PROJECT INFO
    QColor checkerLightColor; // PROJECT INFO
    QImage backgroundImage;
    QImage displayImage; //just for display (not saved anywhere)--includes matte, canvas (checkerboard), and interface
    QList<RotoCanvasLayer*> layerPtrs;
    QPoint lastPoint;

    //project info:
    //QString formatString;
};
//! [0]

#endif
