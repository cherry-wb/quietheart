package demo;

import org.jfree.chart.JFreeChart;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartFrame;
import org.jfree.data.general.DefaultPieDataset;

public class FirstJFreeChart {
  public FirstJFreeChart() {
  }
  
  public static void main(String[] args){
    DefaultPieDataset dpd = new DefaultPieDataset();//建立饼形图数据对象
    //设置饼形图的显示
    dpd.setValue("采集数据",25);
    dpd.setValue("处理数据",25);
    dpd.setValue("控制算法",45);
    dpd.setValue("生成配时方案",5);
    
    //Create JFreeChart object
    //参数可以查看源码
    JFreeChart pieChart = ChartFactory.createPieChart("智能交通项目内容",dpd,true,true,false);
    ChartFrame pieFrame = new ChartFrame("智能交通项目内容",pieChart);
    pieFrame.pack();
    pieFrame.setVisible(true);
  }
}
