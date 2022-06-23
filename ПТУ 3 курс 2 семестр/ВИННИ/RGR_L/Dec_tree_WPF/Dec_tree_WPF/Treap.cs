using System;
using System.Collections.Generic;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

namespace Dec_tree_WPF
{
    class Treap
    {
        public int x;
        public int y;

        public Treap Left;
        public Treap Right;

        static Random rand = new Random();

        static void Next_Step(ref Treap temp_treap, int x)
        {

        }
        public Treap(int x, int y, Treap left = null, Treap right = null)
        {
            this.x = x;
            this.y = y;
            this.Left = left;
            this.Right = right;
        }

        public static Treap Merge(Treap L, Treap R)
        {
            if (L == null) return R;
            if (R == null) return L;

            if (L.y > R.y)
            {
                var newR = Merge(L.Right, R);
                return new Treap(L.x, L.y, L.Left, newR);
            }
            else
            {
                var newL = Merge(L, R.Left);
                return new Treap(R.x, R.y, newL, R.Right);
            }
        }
        public void Split(int x, out Treap L, out Treap R)
        {
            Treap newTree = null;
            if (this.x <= x)
            {
                if (Right == null)
                    R = null;
                else
                    Right.Split(x, out newTree, out R);
                L = new Treap(this.x, y, Left, newTree);
            }
            else
            {
                if (Left == null)
                    L = null;
                else
                    Left.Split(x, out L, out newTree);
                R = new Treap(this.x, y, newTree, Right);
            }
        }
        public Treap Add(int x)
        {
            Treap l, r;
            Split(x, out l, out r);
            Treap m = new Treap(x, rand.Next(100));
            return Merge(Merge(l, m), r);
        }
        public Treap Add(int x, int y)
        {
            Treap l, r;
            Split(x, out l, out r);
            Treap m = new Treap(x, y);
            return Merge(Merge(l, m), r);
        }
        public Treap Remove(int x)
        {
            Treap l, m, r;
            Split(x - 1, out l, out r);
            r.Split(x, out m, out r);
            return Merge(l, r);
        }
        static public void Counts_of_elements(Treap root, ref List<(int, int)> elements, ref List<(int, int)> elemets_prior, int lvl, ref List<List<(int, int)>> drawed_elem)
        {
            if (root != null)
            {
                if (elements.Count == lvl)
                {
                    elements.Add((0, 0));
                    drawed_elem.Add(new List<(int, int)>());
                }
                elements[lvl] = (elements[lvl].Item1 + 1, 0);
                elemets_prior.Add((root.x, root.y));
                drawed_elem[lvl].Add((root.x, root.y));
                Treap.Counts_of_elements(root.Left, ref elements, ref elemets_prior, lvl + 1, ref drawed_elem);
                Treap.Counts_of_elements(root.Right, ref elements, ref elemets_prior, lvl + 1, ref drawed_elem);
            }
            else
            {
                if(drawed_elem.Count == lvl)
                {
                    drawed_elem.Add(new List<(int, int)>());
                }
                drawed_elem[lvl].Add((-1, -1));
            }
        }

        static public bool Draw_Part_Tree(Treap root, ref Canvas canvas, int lvl, int lvl_border, int width, int section_top, int index, ref Line line)
        {
            if (root == null || lvl == lvl_border)
            {
                return false;
            }
            else
            {
                Ellipse ellipse = new Ellipse();
                ellipse.Height = 20;
                ellipse.Width = 20;
                ellipse.Stroke = Brushes.Black;
                Label label = new Label();
                label.Content = root.x;
                Ellipse ellipse_1 = new Ellipse();
                ellipse_1.Width = ellipse_1.Height = 20;
                ellipse_1.Stroke = Brushes.Red;
                Label label_1 = new Label();
                label_1.Content = root.y;
                label_1.Foreground = Brushes.Red;
                Grid grid = new Grid();
                grid.Children.Add(ellipse);
                grid.Children.Add(label);
                Grid grid_1 = new Grid();
                grid_1.Children.Add(ellipse_1);
                grid_1.Children.Add(label_1);
                int count_of_space = 1 + (int)Math.Pow(2, (double)lvl);
                int section_left = (int)width / count_of_space;
                Canvas.SetLeft(grid, section_left * (index + 2 - Math.Pow(2, (double)lvl)));
                Canvas.SetTop(grid, section_top * (lvl + 1));
                Canvas.SetLeft(grid_1, (section_left * (index + 2 - Math.Pow(2, (double)lvl))) + 7);
                Canvas.SetTop(grid_1, section_top * (lvl + 1) + 7);
                line.X2 = section_left * (index + 2 - Math.Pow(2, (double)lvl)) + 12;
                line.Y2 = section_top * (lvl + 1) + 4;
                canvas.Children.Add(grid);
                canvas.Children.Add(grid_1);
                Line line_1 = new Line();
                Line line_2 = new Line();
                line_1.X1 = section_left * (index + 2 - Math.Pow(2, (double)lvl)) + 11;
                line_1.Y1 = section_top * (lvl + 1) + 23;
                line_2.X1 = section_left * (index + 2 - Math.Pow(2, (double)lvl)) + 11;
                line_2.Y1 = section_top * (lvl + 1) + 23;
                if (Treap.Draw_Part_Tree(root.Left, ref canvas, lvl + 1, lvl_border, width, section_top, index * 2 + 1, ref line_1))
                {
                    line_1.Stroke = Brushes.Black;
                    line_1.StrokeThickness = 1;
                    canvas.Children.Add(line_1);
                }
                if (Treap.Draw_Part_Tree(root.Right, ref canvas, lvl + 1, lvl_border, width, section_top, index * 2 + 2, ref line_2))
                {
                    line_2.Stroke = Brushes.Black;
                    line_2.StrokeThickness = 1;
                    canvas.Children.Add(line_2);
                }
                return true;
            }
        }

        static public bool Draw_Tree(Treap root, ref Canvas canvas, int lvl, int width, int section_top, int index, ref Line line)
        {
            if (root == null)
            {
                return false;
            }
            else
            {
                Ellipse ellipse = new Ellipse();
                ellipse.Height = 20;
                ellipse.Width = 20;
                ellipse.Stroke = Brushes.Black;
                Label label = new Label();
                label.Content = root.x;
                Ellipse ellipse_1 = new Ellipse();
                ellipse_1.Width = ellipse_1.Height = 20;
                ellipse_1.Stroke = Brushes.Red;
                Label label_1 = new Label();
                label_1.Content = root.y;
                label_1.Foreground = Brushes.Red;
                Grid grid = new Grid();
                grid.Children.Add(ellipse);
                grid.Children.Add(label);
                Grid grid_1 = new Grid();
                grid_1.Children.Add(ellipse_1);
                grid_1.Children.Add(label_1);
                int count_of_space = 1 + (int)Math.Pow(2, (double)lvl);
                int section_left = (int)width / count_of_space;
                Canvas.SetLeft(grid, section_left * (index + 2 - Math.Pow(2, (double)lvl)));
                Canvas.SetTop(grid, section_top * (lvl + 1));
                Canvas.SetLeft(grid_1, (section_left * (index + 2 - Math.Pow(2, (double)lvl))) + 7);
                Canvas.SetTop(grid_1, section_top * (lvl + 1) + 7);
                line.X2 = section_left * (index + 2 - Math.Pow(2, (double)lvl)) + 12;
                line.Y2 = section_top * (lvl + 1) + 4;
                canvas.Children.Add(grid);
                canvas.Children.Add(grid_1);
                Line line_1 = new Line();
                Line line_2 = new Line();
                line_1.X1 = section_left * (index + 2 - Math.Pow(2, (double)lvl)) + 11;
                line_1.Y1 = section_top * (lvl + 1) + 23;
                line_2.X1 = section_left * (index + 2 - Math.Pow(2, (double)lvl)) + 11;
                line_2.Y1 = section_top * (lvl + 1) + 23;
                if(Treap.Draw_Tree(root.Left, ref canvas, lvl + 1, width, section_top, index * 2 + 1, ref line_1))
                {
                    line_1.Stroke = Brushes.Black;
                    line_1.StrokeThickness = 1;
                    canvas.Children.Add(line_1);
                }
                if(Treap.Draw_Tree(root.Right, ref canvas, lvl + 1, width, section_top, index * 2 + 2, ref line_2))
                {
                    line_2.Stroke = Brushes.Black;
                    line_2.StrokeThickness = 1;
                    canvas.Children.Add(line_2);
                }
                return true;
            }
        }
    }
}
