/**************************************************************************************************************
*函数功能：改变控件的背景图片
*filename:图片文件的路径
*widget：要改变背景的控件
*该函数不能改变所有控件的背景，只能对部分控件起作用
***************************************************************************************************************/
static void set_background_pixmap(const gchar *filename,GtkWidget *widget)
{
       GdkPixbuf *pbuf,*bg;
       GdkPixmap *pixmap;
       gint width,height;

       if(GTK_WIDGET_NO_WINDOW(widget))
       {
            g_print("the widget has not window\n");   
       }
  
       if(!GTK_WIDGET_REALIZED(widget))
       {
             gtk_widget_realize(widget);
       }
  
       if(!filename)
       {
             gdk_window_set_back_pixmap(widget->window,NULL,FALSE);
       }
 
       pbuf = gdk_pixbuf_new_from_file(filename,NULL);
       if(!pbuf)
       {
            g_print("fail\n"); 
            return;
       }
       width = gdk_pixbuf_get_width(pbuf);
       height = gdk_pixbuf_get_height(pbuf);

       bg = gdk_pixbuf_new(GDK_COLORSPACE_RGB,TRUE,
               gdk_pixbuf_get_bits_per_sample(pbuf),width,height);
       gdk_pixbuf_fill(bg,0);
       gdk_pixbuf_composite(pbuf,bg,0,0,width,height,0,0,1,1,
               GDK_INTERP_BILINEAR,0xFF);
  
       pixmap = gdk_pixmap_new(widget->window,width,height,-1);
       gdk_draw_pixbuf(pixmap,NULL,pbuf,0,0,0,0,-1,-1,
               GDK_RGB_DITHER_NORMAL,1,1);
 
       gdk_pixbuf_unref(pbuf);
       gdk_pixbuf_unref(bg);
    
       gdk_draw_drawable(widget->window, widget->style->fg_gc[GTK_WIDGET_STATE(widget)],
               pixmap,
               0, 0,
               0, 0,
               width, height);
       gtk_widget_set_app_paintable(widget,TRUE);
       gdk_window_set_back_pixmap(widget->window,pixmap,FALSE);

       gtk_widget_queue_draw(widget);
}
