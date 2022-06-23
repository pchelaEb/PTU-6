using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;

namespace Dec_tree_WPF
{
    class Tree_Info
    {
        public int size = 0;
        public List<(int, int)> elements_on_lvl = new List<(int, int)>();
        public List<(int, int)> elements_priority = new List<(int, int)>();
        public List<List<(int, int)>> drawed_elements = new List<List<(int, int)>>();
        public Treap treap;
        public int lvl = 0;
        public int number_slide = -1;
        public STEPS step = STEPS.ONE;
        public List<List<UIElement>> previous = new List<List<UIElement>>();
        public List<string> comments = new List<string>();

        public enum STEPS
        {
            ZERO,
            ONE,
            TWO,
        }

        public void Reset()
        {
            step = STEPS.ZERO;
            elements_on_lvl.Clear();
            elements_priority.Clear();
            drawed_elements.Clear();
            drawed_elements = new List<List<(int, int)>>();
            previous.Clear();
            comments.Clear();
            treap = null;
            lvl = 0;
            number_slide = -1;
        }

        public List<(int, int)> Get_Element()
        {
            List<(int, int)> result = new List<(int, int)>();
            if (elements_on_lvl[lvl].Item1 != 0)
            {
                result = drawed_elements[lvl];
            }
            return result;
        }
    }
}
