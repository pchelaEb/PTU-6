using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Threading;

namespace Dec_tree_WPF
{
    public partial class MainWindow : Window
    {
        Treap tree = null;
        Tree_Info info = new Tree_Info();
        List<(int, int)> buf = new List<(int, int)>();
        public MainWindow()
        {
            InitializeComponent();
            info.treap = new Treap(40, 78);
            info.treap = info.treap.Add(21, 32);
            info.treap = info.treap.Add(65, 33);
            Line line = new Line();
            Treap.Draw_Tree(info.treap, ref canvas_preview, 0, (int)canvas_preview.Width, 30, 0, ref line);
        }

        private void button2_Click(object sender, RoutedEventArgs e)
        {
            if (int.TryParse(textBox.Text, out int result))
            {
                info.size = result;
                note.Text = "";
                Random rand = new Random();
                tree = new Treap(rand.Next(100), rand.Next(100));
                info.Reset();
                for (int i = 0; i < info.size - 1; i++)
                {
                    tree = tree.Add(rand.Next(100));
                }
                bool check = true;
                while (check)
                {
                    Treap.Counts_of_elements(tree, ref info.elements_on_lvl, ref info.elements_priority, 0, ref info.drawed_elements);
                    for (int i = 0; i < info.elements_on_lvl.Count; i++)
                    {
                        check = false;
                        if (i > 4 && info.elements_on_lvl[i].Item1 > 1)
                        {
                            check = true;
                            break;
                        }
                    }
                    if (check)
                    {
                        tree = new Treap(rand.Next(100), rand.Next(100));
                        info.Reset();
                        for (int i = 0; i < info.size - 1; i++)
                        {
                            tree = tree.Add(rand.Next(100));
                        }
                    }
                }
                Draw_elements();
            }
            else
            {
                note.Text = "Введите размер дерева";
            }
        }
        public void Next_Step(object sender, RoutedEventArgs e)
        {
            if (info.number_slide == -1 || info.number_slide + 1 == info.previous.Count)
            {
                if (info.elements_priority.Count == 0 && info.step == Tree_Info.STEPS.ONE)
                    return;
                canvas.Children.Clear();
                if (info.step == Tree_Info.STEPS.TWO)
                {
                    info.step = Tree_Info.STEPS.ZERO;
                }
                info.step++;
                Draw_Step(ref info.elements_priority);
            }
            else
            {
                canvas.Children.Clear();
                info.number_slide++;
                foreach(UIElement elem in info.previous[info.number_slide])
                {
                    canvas.Children.Add(elem);
                }
                note.Text = info.comments[info.number_slide];
            }
        }

        public void Previous_Step(object sender, RoutedEventArgs e)
        {
            if(info.number_slide > 0)
            {
                canvas.Children.Clear();
                info.number_slide--;
                foreach (UIElement elem in info.previous[info.number_slide])
                {
                    canvas.Children.Add(elem);
                }
                note.Text = info.comments[info.number_slide];
            }
        }

        void Draw_Elem(int i, (int, int) elem, int height, int count, bool bold = false)
        {
            Ellipse ellipse = new Ellipse();
            ellipse.Height = 20;
            ellipse.Width = 20;
            Label label = new Label();
            label.Content = elem.Item1;
            Ellipse ellipse_1 = new Ellipse();
            ellipse_1.Width = ellipse_1.Height = 20;
            Label label_1 = new Label();
            label_1.Content = elem.Item2;
            if (bold)
            {
                label.FontWeight = FontWeights.UltraBold;
                label_1.FontWeight = FontWeights.UltraBold;
            }
            ellipse.Stroke = Brushes.Black;
            ellipse_1.Stroke = Brushes.Red;
            label_1.Foreground = Brushes.Red;
            Grid grid = new Grid();
            grid.Children.Add(ellipse);
            grid.Children.Add(label);
            Grid grid_1 = new Grid();
            grid_1.Children.Add(ellipse_1);
            grid_1.Children.Add(label_1);
            Canvas.SetLeft(grid, (i + 1) * (canvas.ActualWidth / (count + 1)));
            Canvas.SetTop(grid, height);
            Canvas.SetLeft(grid_1, (i + 1) * canvas.ActualWidth / (count + 1) + 7);
            Canvas.SetTop(grid_1, height + 7);
            canvas.Children.Add(grid);
            canvas.Children.Add(grid_1);
        }

        private void Draw_Step(ref List<(int, int)> elements_prior)
        {
            switch (info.step)
            {

                case Tree_Info.STEPS.ONE:
                    Line line = new Line();
                    Treap.Draw_Part_Tree(tree, ref canvas, 0, info.lvl, (int)grid_canvas.Width, 40, 0, ref line);
                    for (int i = 0; i < elements_prior.Count; i++)
                    {
                        Draw_Elem(i, elements_prior[i], 370, elements_prior.Count);
                    }
                    if(info.lvl != info.elements_on_lvl.Count)
                    {
                        buf = info.Get_Element();
                    }
                    info.previous.Add(new List<UIElement>());
                    info.number_slide++;
                    foreach(UIElement elem in canvas.Children)
                    {
                        info.previous[info.number_slide].Add(elem);
                    }
                    if(info.lvl == 0)
                    {
                        note.Text = "При построении декартового дерева корнем дерева выбирается " +
                            "элемент имеющий максимальный приоритет";
                    }
                    else
                    {
                        if(info.lvl - 1 == 0)
                        {
                            note.Text = "Производим вставку элемента в корень";
                        }
                        else
                        {
                            var null_elem = (from e in info.drawed_elements[info.lvl - 1]
                                             where e == (-1, -1)
                                             select e).Count();
                            if (null_elem > 0 && info.lvl != info.elements_on_lvl.Count)
                            {
                                string not_full = "";
                                List<(int, int)> element = new List<(int, int)>();
                                while(info.drawed_elements[info.lvl - 2].Contains((-1, -1)))
                                {
                                    info.drawed_elements[info.lvl - 2].Remove((-1, -1));
                                }
                                for(int i = 0; i < info.drawed_elements[info.lvl - 1].Count; i++)
                                {
                                    if(info.drawed_elements[info.lvl - 1][i] == (-1, -1))
                                    {
                                        if (!element.Contains(info.drawed_elements[info.lvl - 2][i / 2]))
                                        {
                                            not_full += info.drawed_elements[info.lvl - 2][i / 2].ToString() + ", ";
                                            element.Add(info.drawed_elements[info.lvl - 2][i / 2]);
                                        }
                                    }
                                }
                                not_full = not_full.Remove(not_full.Length - 2);
                                note.Text = $"Были вставлены не все элементы которые можно вместить на данный уровень" +
                                    $", а только {info.drawed_elements[info.lvl - 1].Count - null_elem}, так как" +
                                    $" не хватает элементов удовлетворяющих условию для следующих корней: " + not_full;
                            }
                            else
                            {
                                note.Text = "Производим вставку элементов в дерево";
                            }
                        }
                    }
                    info.comments.Add(note.Text);
                    break;
                case Tree_Info.STEPS.TWO:
                    line = new Line();
                    Treap.Draw_Part_Tree(tree, ref canvas, 0, info.lvl, (int)grid_canvas.Width, 40, 0, ref line);
                    for (int i = 0; i < elements_prior.Count; i++)
                    {
                        if (buf.Contains(elements_prior[i]))
                        {
                            Draw_Elem(i, elements_prior[i], 357, elements_prior.Count, true);
                        }
                        else
                        {
                            Draw_Elem(i, elements_prior[i], 370, elements_prior.Count);
                        }
                    }
                    elements_prior.RemoveAll(e => buf.Contains(e));
                    if(info.lvl == 0)
                    {
                        note.Text = $"В данном случае корнем дерева будет элемент {buf[0]}" +
                            $" где {buf[0].Item1} само хранимое значение, {buf[0].Item2} - его приоритет";
                    }
                    else
                    {
                        string insert_elem = "";
                        foreach(var e in buf)
                        {
                            if (e != (-1, -1))
                            {
                                insert_elem += e.ToString() + ", ";
                            }
                        }
                        insert_elem = insert_elem.Remove(insert_elem.Length - 2);
                        note.Text = "Для вставки были выбраны следующие элементы: " + insert_elem; 
                    }
                    info.lvl++;
                    info.previous.Add(new List<UIElement>());
                    info.comments.Add(note.Text);
                    info.number_slide++;
                    foreach (UIElement elem in canvas.Children)
                    {
                        info.previous[info.number_slide].Add(elem);
                    }
                    break;
            }
        }
        public void Draw_elements()
        {
            canvas.Children.Clear();
            Line line = new Line();
            Treap.Draw_Tree(tree, ref canvas, 0, (int)grid_canvas.Width, 40, 0, ref line);
        }
    }
}
