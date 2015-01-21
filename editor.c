#include "types.h"
#include "uwindow.h"
#include "stat.h"
#include "user.h"


static TextBox text_box;
Window window;
static int hWind;
RGB closeButtonImageViewTemp[100];
RGB saveButtonImageViewTemp[100];
ImageView closeButtonImageView;
ImageView saveButtonImageView;

static void initText();
void closeWindow(Widget *widget, Window *window);
void saveFile(int fd);

void cat(int fd)
{
  int n;

  while((n = read(fd, text_box.text, sizeof(text_box.text))) > 0)
    write(1, text_box.text, n);
  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

int main(int argc,char *argv[])
{
  int fd;
  memset(&window, 0, sizeof(Window));
  window.leftTopX = 300;
  window.leftTopY = 200;
  window.width = 600;
  window.height = 500;
  window.show = 1;
  window.hasCaption = 1;
  strcpy(window.caption, "TextEditor");

  addCloseButton(&window, &closeButtonImageView, closeButtonImageViewTemp);
  closeButtonImageView.onLeftClickHandler.handlerFunction = closeWindow;

//  addSaveButton(&window,&saveButtonImageView,saveButtonImageViewTemp);
//  saveButtonImageView.onLeftClickHandler.handlerFunction = saveFile;

  if (strcmp(argv[0], "editor") != 0)
  {
    initText();
    memset(&text_box, 0, sizeof(TextBox));
    if((fd = open(argv[0], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[1]);
      exit();
    }
    cat(fd);
      //close(fd);
strcpy(text_box.text, "adsfadsf");
    text_box.leftTopX = (window.width >> 1) - (text_box.width >> 1);
    text_box.leftTopY = (window.height >> 1) - (text_box.height >> 1);
    window.widgets[window.widgetsNum].type = textBox;
    window.widgets[window.widgetsNum].context.textBox = &text_box;
    window.widgetsNum++;
  }
printf(1, "haha\n");
  hWind = createWindow(&window);
  while(1)
  {
    handleEvent(&window);
  }
  exit();
}

static void initText()
{
  text_box.leftTopX = 20;
  text_box.leftTopY = 20;
  text_box.width = 500;
  text_box.height = 400;
  text_box.text[0] = '\0';
  text_box.cursor = 0;
  text_box.semoph = 1;
}

void closeWindow(Widget *widget, Window *window)
{
  deleteWindow(hWind);
  exit();
}

void saveFile(int fd)
{
  //file name :text1,text2...
  //file content text_box.content
  write(fd, text_box.content, strlen(text_box.content));
}

